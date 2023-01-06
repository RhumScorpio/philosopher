/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clesaffr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 19:53:38 by clesaffr          #+#    #+#             */
/*   Updated: 2023/01/06 20:27:19 by clesaffr         ###   ########.fr       */
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

int	parsing_rules(char **av, &rules)
{
	rules->nbr_philos = ft_atoi(av[1]);
	rules->t_die = ft_atoi(av[2]);
	rules->t_eat = ft_atoi(av[3]);
	rules->t_sleep = ft_atoi(av[4]);
	if (rules->nbr_philos > 250 || rules->nbr_philos < 0 || rules->t_die < 0 ||
			rules->t_eat < 0 || rules->t_sleep < 0)
			return (1);
	if (av[5])
	{
		rules->nbr_eats = ft_atoi(av[5]);
		if (rules->nbr_eats < 0)
			return (1);
	}
	return (3);
}

int main(int ac, char **av)
{
	t_philorules	rules;

	if (ac != 5 || ac != 6)
		return (put_error("Wrong number of arguments."));
	parsing_rules(av, &rules);
	return (0);
}
