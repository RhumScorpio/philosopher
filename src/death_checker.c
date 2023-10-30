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
#include "../philosophers.h"

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
	int	i;

	i = 0;
	pthread_mutex_lock(&(rules->death_check));
	i = rules->death;
	pthread_mutex_unlock(&(rules->death_check));
	if (i)
		return (1);
	else
		return (0);
}

void	put_death(t_philorules *rules, t_philo *philo)
{
	pthread_mutex_lock(&(rules->writing));
	pthread_mutex_lock(&(rules->death_check));
	rules->death = 1;
	pthread_mutex_unlock(&(rules->death_check));
	printf("%lli ", timestamp() - rules->start_time);
	printf("%d ", philo->id + 1);
	printf("%s\n", "died");
	pthread_mutex_unlock(&(rules->writing));
}

void	stop_for_ate_all(t_philorules *rules)
{
	pthread_mutex_lock(&(rules->death_check));
	rules->death = 1;
	pthread_mutex_unlock(&(rules->death_check));
}
