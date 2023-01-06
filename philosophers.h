/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clesaffr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:19:23 by clesaffr          #+#    #+#             */
/*   Updated: 2023/01/06 21:44:33 by clesaffr         ###   ########.fr       */
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

typedef struct	s_timestamp
{
	time_t      tv_sec;
	suseconds_t tv_usec;
}				t_timestamp;

typedef struct	s_philo
{
	int					id;
	int					ate;
	int					left_fork;
	int					right_fork;
	t_timestamp			timestamp_ate;
	pid_t				proc_id;
	pthread_t			death_check;
	struct s_philorules	*rules;
}				t_philo;

typedef struct	s_philorules
{
	int			nbr_philos;
	int			t_die;
	int			t_eat;
	int			t_sleep;
	int			nbr_eats;
	int			death;
	t_timestamp	first_timestamp;
	t_philo		philos[250];
}				t_philorules;

#endif
