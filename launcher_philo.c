/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher_philo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clesaffr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 20:07:01 by clesaffr          #+#    #+#             */
/*   Updated: 2023/03/02 17:09:23 by clesaffr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

static void	put_meal(t_philo *philo)
{
	t_philorules	*rules;

	rules = philo->rules;
	print_philo(philo, "is eating");
	pthread_mutex_lock(&(rules->meal_check));
	philo->timestamp = timestamp();
	pthread_mutex_unlock(&(rules->meal_check));
	my_sleep(rules->t_eat, philo);
	if (rules->total_meals)
		(philo->nb_meals)++;
}

static int	philo_eating(t_philo *philo)
{
	t_philorules	*rules;

	rules = philo->rules;
	if (rules->nbr_philos == 1)
		return (0);
	take_left_fork(philo);
	if (death_check(rules))
		return (put_left_fork_back(philo));
	take_right_fork(philo);
	if (death_check(rules))
		return (put_right_fork_back(philo));
	put_meal(philo);
	return (put_right_fork_back(philo));
}

static void	*launch_thread(void *void_philo)
{
	t_philo			*philo;
	t_philorules	*rules;

	philo = (t_philo *)void_philo;
	rules = philo->rules;
	if (philo->id % 2 == 0)
	{
		print_philo(philo, "is thinking");
		usleep(rules->t_eat);
	}
	while (!death_check(rules))
	{
		if (!philo_eating(philo))
			break ;
		if (death_check(rules))
			break ;
		print_philo(philo, "is sleeping");
		my_sleep(rules->t_sleep, philo);
		print_philo(philo, "is thinking");
	}
	return (NULL);
}

int	launch(t_philorules *rules)
{
	t_philo	*philos;
	int		i;

	philos = rules->philos;
	i = 0;
	while (i < rules->nbr_philos)
	{
		philos[i].timestamp = timestamp();
		pthread_create(&(philos[i].philothread), NULL,
			&launch_thread, &philos[i]);
		i++;
	}
	pthread_create(&(rules->monitor), NULL, &monitor, rules);
	pthreadjoin_for_death(rules);
	return (1);
}
