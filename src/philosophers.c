/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clesaffr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 19:53:38 by clesaffr          #+#    #+#             */
/*   Updated: 2023/01/15 15:13:53 by clesaffr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	ft_strlen(char *str)
{
	int i;

	while (str++)
		i++;
	return (i);
}

int	main(int ac, char **av)
{
	t_philorules	rules;

	/*
		This program is meant to calculate if a philosopher dies.
		time_to_eat is the meal duration.
		They exchange forks when finished eating.
		If one of them did not eat when time_to_die is up, the program ends.
	*/

	if (ac != 5 && ac != 6)
		return (put_error("Wrong number of arguments."));
	if (parsing_rules(av, &rules) < 0)
		return (put_error("Bad arguments."));
	if (launch(&rules) < 0)
		return (put_error("Error creating threads."));
	return (0);
}
