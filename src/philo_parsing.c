/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clesaffr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 20:04:40 by clesaffr          #+#    #+#             */
/*   Updated: 2023/03/24 12:25:40 by clesaffr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philosophers.h"

static int	ft_atoi(const char *str)
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

int	parsing_rules(char **av, t_philorules *rules)
{
	rules->nbr_philos = ft_atoi(av[1]);
	rules->t_die = ft_atoi(av[2]);
	rules->t_eat = ft_atoi(av[3]);
	rules->t_sleep = ft_atoi(av[4]);
	rules->total_meals = -1;
	rules->death = 0;
	if (rules->nbr_philos > 200 || rules->nbr_philos < 1 || rules->t_die < 0
		|| rules->t_eat < 0 || rules->t_sleep < 0)
		return (-1);
	if (av[5])
	{
		rules->total_meals = ft_atoi(av[5]);
		if (rules->total_meals <= 0)
			return (-1);
	}
	init_philos(rules);
	return (init_rules(rules));
}
