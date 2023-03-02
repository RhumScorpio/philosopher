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
	long long		time;

	rules = philo->rules;
	time = timestamp() - rules->start_time;
	pthread_mutex_lock(&(rules->writing));
	if (!death_check(rules))
		printf("%s%lli %s%d %s%s%s\n", KGRN, time, KRED, philo->id,
			KMAG, str, KNRM);
	pthread_mutex_unlock(&(rules->writing));
}
