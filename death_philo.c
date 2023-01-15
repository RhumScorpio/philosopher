/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clesaffr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 20:08:46 by clesaffr          #+#    #+#             */
/*   Updated: 2023/01/15 16:45:00 by clesaffr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

int	pthreadjoin_for_death(t_philorules *rules)
{
	t_philo	*philos;
	int		i;

	philos = rules->philos;
	i = -1;
	while (++i < rules->nbr_philos)
		pthread_join(philos[i].philothread, NULL);
	pthread_join(rules->monitor, NULL);
	i = -1;
	while (++i < rules->nbr_philos)
		pthread_mutex_destroy(&(rules->forks[i]));
	pthread_mutex_destroy(&(rules->writing));
	pthread_mutex_destroy(&(rules->meal_check));
	pthread_mutex_destroy(&(rules->death_check));
	return (1);
}

static int	ate_all(int max, t_philo *philos, int nbr_philos)
{
	int	i;
	int	total;

	i = 0;
	total = 0;
	if (!max)
		return (0);
	while (i < nbr_philos)
	{
		if (philos[i].nb_meals >= max)
			total++;
		i++;
	}
	if (total == nbr_philos)
		return (1);
	else
		return (0);
}

void	*monitor(void *void_rules)
{
	t_philorules	*rules;
	t_philo			*philos;
	int				i;

	rules = (t_philorules *)void_rules;
	philos = rules->philos;
	while (death_check(rules) != 1)
	{
		i = 0;
		while (death_check(rules) != 1 && i < rules->nbr_philos)
		{
			if (death_by_starving(&philos[i]) >= rules->t_die)
			{
				print_philo(&philos[i], "is dead.");
				put_death(rules);
			}
			i++;
		}
		if (death_check(rules))
			break ;
		if (ate_all(rules->total_meals, philos, rules->nbr_philos))
			put_death(rules);
	}
	return (NULL);
}
