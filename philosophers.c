/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clesaffr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 19:53:38 by clesaffr          #+#    #+#             */
/*   Updated: 2023/01/14 20:23:06 by clesaffr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int ac, char **av)
{
	t_philorules	rules;

	if (ac != 5 && ac != 6)
		return (put_error("Wrong number of arguments : nbr / die / eat / sleep / meals."));
	if (parsing_rules(av, &rules) < 0)
		return (put_error("Bad arguments."));
	if (launch(&rules) < 0)
		return (put_error("Error creating threads."));
	return (0);
}
