/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_philo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clesaffr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 20:05:54 by clesaffr          #+#    #+#             */
/*   Updated: 2023/01/15 02:01:02 by clesaffr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

void	init_philos(t_philorules *rules)
{
	int	i;
	int	total_philos;

	i = 0;
	total_philos = rules->nbr_philos;
	while (i < total_philos)
	{
		rules->philos[i].id = i;
		rules->philos[i].nb_meals = 0;
		rules->philos[i].timestamp = 0;
		rules->philos[i].left_fork = i;
		rules->philos[i].right_fork = (i + 1) % total_philos;
		rules->philos[i].rules = rules;
		i++;
	}
}

static int mutex_error(void)
{
	printf("Bad mutex init.\n");
	return (-1);
}

int init_rules(t_philorules *rules)
{
	int	i;

	i = -1;
	rules->start_time = timestamp();
	while (++i < rules->nbr_philos)
	{
		if (pthread_mutex_init(&rules->forks[i], NULL))
			return (mutex_error());
	}
	if (pthread_mutex_init(&rules->writing, NULL))
		return (mutex_error());
	if (pthread_mutex_init(&rules->meal_check, NULL))
		return (mutex_error());
	if (pthread_mutex_init(&rules->death_check, NULL))
		return (mutex_error());
	return (1);
}
