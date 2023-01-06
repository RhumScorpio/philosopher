/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clesaffr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:19:23 by clesaffr          #+#    #+#             */
/*   Updated: 2023/01/06 19:57:16 by clesaffr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>

typedef struct s_philorules
{
	int	nbr_philos;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	nbr_eats;
}				t_philorules;

#endif
