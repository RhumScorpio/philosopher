/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clesaffr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:19:23 by clesaffr          #+#    #+#             */
/*   Updated: 2023/03/24 12:22:55 by clesaffr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>
# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# define KMAG  "\x1B[35m"
# define KCYN  "\x1B[36m"

struct	s_philorules;

typedef struct s_philo
{
	int					id;
	int					nb_meals;
	int					left_fork;
	int					right_fork;
	long long			timestamp;
	pthread_t			philothread;
	struct s_philorules	*rules;
}				t_philo;

typedef struct s_philorules
{
	int				nbr_philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				total_meals;
	int				death;
	long long		start_time;
	t_philo			philos[200];
	pthread_mutex_t	forks[200];
	pthread_mutex_t	writing;
	pthread_mutex_t	meal_check;
	pthread_mutex_t	death_check;
	pthread_t		monitor;
}				t_philorules;

//DIE
int			death_by_starving(t_philo *philo);
void		put_death(t_philorules *rules, t_philo *philo);
int			death_check(t_philorules *rules);
int			pthreadjoin_for_death(t_philorules *rules);
void		stop_for_ate_all(t_philorules *rules);

// SLEEP THINK
long long	timestamp(void);
int			my_sleep(int time, t_philo *philo);

//EAT
void		print_philo(t_philo *philo, char *str);
// fork exchange
void		take_left_fork(t_philo *philo);
void		take_right_fork(t_philo *philo);

//LAUNCH
int			launch(t_philorules *rules);
void		*monitor(void *void_rules);

// INIT
int			parsing_rules(char **av, t_philorules *rules);
int			put_error(char *str);
int			init_rules(t_philorules *rules);
void		init_philos(t_philorules *rules);

#endif
