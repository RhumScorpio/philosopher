/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clesaffr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 19:53:38 by clesaffr          #+#    #+#             */
/*   Updated: 2023/01/11 18:48:48 by clesaffr         ###   ########.fr       */
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
	printf("%s\n", str);
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
		rules->philos[i].right_fork = (i + 1) % total_philos;
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

void	print_philo(t_philo *philo, char *str)
{
	printf("time is %lli and PHILO %d %s\n", philo->timestamp, philo->id, str);
}

void	my_sleep(long long t_eat, t_philorules *rules)
{
	long long	i;
	long long	diff;

	i = timestamp();
	diff = 0;
	while (!rules->death)
	{
		usleep(50);
		diff = i - timestamp();
		if (diff >= t_eat)
			break ;
	}
}

void	philo_eating(t_philo *philo)
{
	t_philorules	*rules;

	rules = philo->rules;
	pthread_mutex_lock(&(rules->forks[philo->left_fork]));
	print_philo(philo, "has taken a fork.");
	pthread_mutex_lock(&(rules->forks[philo->left_fork]));
	print_philo(philo, "has taken a fork.");
	pthread_mutex_lock(&(rules->meal_check));
	philo->timestamp = timestamp();
	print_philo(philo, "is eating.");
	my_sleep(rules->t_eat, rules);
	(philo->nb_meals)++;
	pthread_mutex_unlock(&(rules->meal_check));
	pthread_mutex_unlock(&(rules->forks[philo->left_fork]));
	pthread_mutex_unlock(&(rules->forks[philo->right_fork]));
}


int	death_by_starving(long long last_meal, int t_die)
{
	long long	thetime;
	int			res;

	thetime = timestamp();
	res = (int)(thetime - last_meal);
	if (res >= t_die)
		return (1);
	else
		return (0);
}

void	*death_checker(void *void_philo)
{
	t_philorules	*rules;
	t_philo			*philo;
	int				i;
	int				total;

	philo = (t_philo *)void_philo;
	rules = philo->rules;
	i = 0;
	total = 0;
	while (1)
	{
		if (death_by_starving(philo->timestamp, rules->t_die))
			rules->death = 1;
		while (i < rules->nbr_philos)
			if (rules->total_meals > 0 && rules->philos[i].nb_meals >= rules->total_meals)
				total++;
		if (total == rules->nbr_philos)
			rules->death = 1;
	}
	if (rules->death)
		print_philo(philo, "is dead");
}

void	*launch_thread(void *void_philo)
{
	t_philo 		*philo;
	t_philorules	*rules;

	philo = (t_philo *)void_philo;
	rules = philo->rules;
	while (!rules->death)
	{
		philo_eating(philo);
		print_philo(philo, "is thinking.");
		print_philo(philo, "is sleeping.");
		usleep(rules->t_sleep);
	}
}

void	pthreadjoin_for_death(t_philo *philos)
{
	t_philorules	*rules;
	int	i;

	rules = philos->rules;
	i = 0;
	while (i < rules->nbr_philos)
	{
		pthread_join(philos->philothread, NULL);
		i++;
	}
	i = 0;
	while (i++ < rules->nbr_philos)
		pthread_mutex_destroy(&(rules->forks[i]));
	pthread_mutex_destroy(&(rules->meal_check));
}

int	launch(t_philorules *rules)
{
	int	i;
	t_philo	*philos;

	
	philos = rules->philos;
	i = 0;
	pthread_create(&(rules->death_checker), NULL, death_checker, (void *)philos[i]);
	while (i < rules->nbr_philos)
	{
		philos[i].timestamp = timestamp();
		if (pthread_create(&(philos[i].philothread), NULL, launch_thread, (void *)philos[i]))
			return (-1);
		i++;
	}
	pthreadjoin_for_death(philos);
	return (1);
}

int main(int ac, char **av)
{
	t_philorules	rules;

	if (ac != 5 || ac != 6)
		return (put_error("Wrong number of arguments."));
	if (parsing_rules(av, &rules) < 0)
		return (put_error("Bad arguments : ./philo [nbr < 250] [time_to_die] [time_to_eat] [time_to_sleep] (nb meals)"));
	if (launch(&rules) < 0)
		return (put_error("Error creating threads."));
	return (0);
}
