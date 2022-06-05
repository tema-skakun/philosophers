/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 23:57:29 by ulagrezina        #+#    #+#             */
/*   Updated: 2022/06/05 22:33:08 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>

typedef pthread_mutex_t	t_mutex;

typedef struct s_data
{
	t_mutex	*p_mutex;
	int		*num;
}	t_data;

typedef struct s_philo
{
	int		num_of_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_of_times;
	t_mutex	*left;
	t_mutex	*right;
}	t_philo;

void	validation_and_parcing(int ac, char **av, t_philo *philo);

#endif