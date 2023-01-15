/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clesaffr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 20:10:18 by clesaffr          #+#    #+#             */
/*   Updated: 2023/01/15 01:51:45 by clesaffr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

long long	timestamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	put_error(char *str)
{
	printf("%s\n", str);
	return (0);
}

void	print_philo(t_philo *philo, char *str)
{
	t_philorules	*rules;
	long long		time;

	rules = philo->rules;
	time = timestamp() - rules->start_time;
	pthread_mutex_lock(&(rules->writing));
	if (!death_check(rules))
		printf("timing %lli | %sPHILO %s%d %s%s%s\n", time, KGRN, KRED, philo->id, KCYN, str, KNRM);
	pthread_mutex_unlock(&(rules->writing));
}

int	my_sleep(int time, t_philo *philo)
{
	t_philorules	*rules;
	long long		timestamp_aim;

	rules = philo->rules;
	timestamp_aim = timestamp() + time;
	while (timestamp() <= timestamp_aim)
	{
		usleep(50);
		if (death_check(rules))
			return (1);
	}
	return (0);
}
