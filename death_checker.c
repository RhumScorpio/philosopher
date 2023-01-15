/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clesaffr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 20:02:55 by clesaffr          #+#    #+#             */
/*   Updated: 2023/01/15 15:02:11 by clesaffr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

int	death_by_starving(t_philo *philo)
{
	t_philorules	*rules;
	long long		res;

	rules = philo->rules;
	pthread_mutex_lock(&(rules->meal_check));
	res = timestamp() - philo->timestamp;
	pthread_mutex_unlock(&(rules->meal_check));
	return ((int)res);
}

int	death_check(t_philorules *rules)
{
	pthread_mutex_lock(&(rules->death_check));
	if (rules->death == 1)
	{
		pthread_mutex_unlock(&(rules->death_check));
		return (1);
	}
	pthread_mutex_unlock(&(rules->death_check));
	return (0);
}

void	put_death(t_philorules *rules)
{
	pthread_mutex_lock(&(rules->death_check));
	rules->death = 1;
	pthread_mutex_unlock(&(rules->death_check));
}
