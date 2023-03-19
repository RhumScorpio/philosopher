/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clesaffr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 01:25:24 by clesaffr          #+#    #+#             */
/*   Updated: 2023/02/27 21:31:38 by clesaffr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

void	print_philo(t_philo *philo, char *str)
{
	t_philorules	*rules;

	rules = philo->rules;
	pthread_mutex_lock(&(rules->writing));
	if (!rules->death)
	{
		printf("%lli ", timestamp() - rules->start_time);
		printf("%d ", philo->id + 1);
		printf("%s\n", str);
	}
	pthread_mutex_unlock(&(rules->writing));
}
