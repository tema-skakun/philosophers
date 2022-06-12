/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jg <jg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 11:42:06 by fdarkhaw          #+#    #+#             */
/*   Updated: 2022/06/12 11:41:53 by jg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct timeval	t_timeval;
typedef pthread_mutex_t	t_mutex;

typedef struct s_philo
{
	int				index;
	int				left_fork;
	int				right_fork;
	int				flag_fork;
	int				count_eat;
	t_timeval		last_eat;
	struct s_data	*data;
	pthread_t		id;
}	t_philo;

typedef struct s_data
{
	int			number_of_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			number_of_times;
	int			counter_times_eaten;
	t_timeval	start;
	t_mutex		forks[200];
	t_mutex		breaker;
	t_mutex		print_lock;
	t_philo		philo[200];
}	t_data;

int				validation(t_data *data, char **av);
int				ft_error(char *msg);
int				init_philosophers(t_data *data);
int				init_forks(t_data *data);
int				start_game(t_data *data);
void			finish_game(t_data *data);
void			*simulation(void *argc);
void			my_sleep(unsigned long ms);
unsigned long	get_time(void);
unsigned long	get_time_in_ms(t_timeval time);
unsigned long	get_cur_time(t_data *sim);

#endif
