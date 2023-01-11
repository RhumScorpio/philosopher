/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clesaffr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:19:23 by clesaffr          #+#    #+#             */
/*   Updated: 2023/01/11 19:07:31 by clesaffr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>

struct s_philorules;

typedef struct	s_philo
{
	int					id;
	int					nb_meals;
	int					left_fork;
	int					right_fork;
	long long			timestamp;
	pthread_t			philothread;
	struct s_philorules	*rules;
}				t_philo;

typedef struct	s_philorules
{
	int				nbr_philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				total_meals;
	int				death;
	t_philo			philos[250];
	pthread_mutex_t	forks[250];
	pthread_mutex_t	meal_check;
}				t_philorules;

#endif
