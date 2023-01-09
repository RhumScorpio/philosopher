/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clesaffr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 19:53:38 by clesaffr          #+#    #+#             */
/*   Updated: 2023/01/09 21:20:53 by clesaffr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	timestamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int			ft_atoi(const char *str)
{
	long int	n;
	int			sign;

	n = 0;
	sign = 1;
	while ((*str <= 13 && *str >= 9) || *str == 32)
		str++;
	if (*str == '-')
		return (-1);
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			n = n * 10 + (*str++ - '0');
		else
			return (-1);
	}
	return ((int)(n * sign));
}

int	put_error(char *str)
{
	ft_putstr(str);
	return (0);
}

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
		rules->philos[i].right_fork = (i + 1) % total_philos
		rules->philos[i].rules = rules;
	}
}

int	parsing_rules(char **av, t_philorules *rules)
{
	rules->nbr_philos = ft_atoi(av[1]);
	rules->t_die = ft_atoi(av[2]);
	rules->t_eat = ft_atoi(av[3]);
	rules->t_sleep = ft_atoi(av[4]);
	if (rules->nbr_philos > 250 || rules->nbr_philos < 0 || rules->t_die < 0 ||
			rules->t_eat < 0 || rules->t_sleep < 0)
			return (-1);
	if (av[5])
	{
		rules->total_meals = ft_atoi(av[5]);
		if (rules->total_meals < 0)
			return (-1);
	}
	init_philos(rules);
	return (1);
}

void	philo_eating(t_philo *philo)
{
	t_philorules	*rules;

	rules = philo->rules;
	pthread_mutex_lock(rules->fork[philo->left_fork]);
	pthread_mutex_lock(rules->fork[philo->left_fork]);
	pthread_mutex_lock(rules->meal_check);
	philo->timestamp = timestamp();
	pthread_mutex_unlock(rules->meal_check);
	pthread_mutex_unlock(rules->fork[philo->left_fork]);
	pthread_mutex_unlock(rules->fork[philo->right_fork]);
	(philo->nb_meals)++;
}

void	*death_checker(void *void_philo)
{
	// 1{ IF TIME EAT DIFF TIMESTAMP < TIME_DEATH
	// 2{ IF NBR MEALS OF ALL PHILOS IS READY 
	//PUT IS DIED
}

int	launch_thread(void *void_philo)
{
	t_philo 		*philo;
	t_philorules	rules;

	philo = (t_philo *)void_philo;
	rules = philo->rules;
	while (!rules->death)
	{
		//philo_eat
		philo_eating(philo);
		//action print thinking
		//action print sleeping
	}
	pthread_join(philo->death_check, NULL);
	if (rules->death)
		exit(1);
}

int	launch(t_philorules *rules)
{
	int	i;
	t_philo	*philos;

	philos = rules->philos;
	i = 0;
	while (i < rules->nbr_philos)
	{
		philos[i].timestamp = timestamp();
		if (pthread_create(&(philos[i].philothread), NULL, launch_thread, (void *)philos[i]))
			return (1);
		i++;
	}
	//death_checker
	//exit_launcher
}

int main(int ac, char **av)
{
	t_philorules	rules;

	if (ac != 5 || ac != 6)
		return (put_error("Wrong number of arguments."));
	if (parsing_rules(av, &rules) < 0)
		return (put_error("Bad arguments : ./philo [nbr < 250]
			[time_to_die] [time_to_eat] [time_to_sleep] (nb meals)"));
	if (launch(&rules) < 0)
		return (put_error("Error creating threads."));
	return (0);
}
