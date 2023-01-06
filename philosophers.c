/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clesaffr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 19:53:38 by clesaffr          #+#    #+#             */
/*   Updated: 2023/01/06 21:44:27 by clesaffr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

	i = 0;
	while (i < rules->nbr_philos)
	{
		rules->philos[i].id = i;
		rules->philos[i].ate = 0;
		rules->philos[i].timestamp_ate = 0;
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
		rules->nbr_eats = ft_atoi(av[5]);
		if (rules->nbr_eats < 0)
			return (-1);
	}
	init_philos(rules);
	return (1);
}

void	*death_checker(void *void_philo)
{
}

int	launch_thread(void *void_philo)
{
	t_philo 		*philo;
	t_philorules	rules;

	philo = (t_philo *)void_philo;
	rules = philo->rules;
	get_time_of_day(&philo->timestamp_ate, NULL);
	pthread_create(&(philo->death_check), NULL, death_checker, void_philo);
}

int	launch(t_philorules *rules)
{
	int	i;
	t_philo	*philos;

	philos = rules->philos;
	i = 0;
	while (i < rules->nbr_philos)
	{
		philos[i].proc_id = fork();
		if (philos[i].proc_id < 0)
			return (-1);
		if (philos[i].proc_id == 0)
			launch_thread(&philos[i]);
		i++;
	}
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
