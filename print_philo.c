/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clesaffr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 01:25:24 by clesaffr          #+#    #+#             */
/*   Updated: 2023/01/15 01:35:34 by clesaffr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

void    print_philo_death(t_philo *philo)
{
    t_philorules    *rules;
    long long       time;

    rules = philo->rules;
    time = timestamp() - rules->start_time;
    pthread_mutex_lock(&(rules->writing_death));
    printf("timing %lli | %sPHILO %s%d %sis dead.%s\n", time, KGRN, KRED, philo->id, KCYN, KNRM);
    pthread_mutex_unlock(&(rules->writing_death));
}
