/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_exchange.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clesaffr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 02:57:32 by clesaffr          #+#    #+#             */
/*   Updated: 2023/03/19 22:33:07 by clesaffr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

void	take_left_fork(t_philo *philo)
{
	t_philorules	*rules;

	rules = philo->rules;
	pthread_mutex_lock(&(rules->forks[philo->left_fork]));
	print_philo(philo, "has taken a fork");
}

void	take_right_fork(t_philo *philo)
{
	t_philorules	*rules;

	rules = philo->rules;
	pthread_mutex_lock(&(rules->forks[philo->right_fork]));
	print_philo(philo, "has taken a fork");
}
