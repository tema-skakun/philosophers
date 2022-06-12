/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jg <jg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 12:17:47 by fdarkhaw          #+#    #+#             */
/*   Updated: 2022/06/12 12:45:41 by jg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_philosophers(t_data *data)
{
	int		i;

	i = 0;
	if (gettimeofday(&data->start, NULL) != 0)
		return (ft_error("the gettimeofday worked incorrectly"));
	while (i < data->number_of_philo)//пока i < кол-ва философов
	{
		data->philo[i].right_fork = i;
		data->philo[i].left_fork = (i + 1) % data->number_of_philo;//операция % возвращает остаток (не дробный хвост)
		data->philo[i].index = i;
		data->philo[i].data = data;
		data->philo[i].last_eat = data->start;
		data->philo[i].count_eat = 0;
		data->philo[i].flag_fork = 0;
		i++;
	}
	return (0);
}

int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&(data->breaker), NULL) != 0)
		return (ft_error("Mutex error"));
	if (pthread_mutex_init(&(data->print_lock), NULL) != 0)
		return (ft_error("Mutex error"));
	while (i < data->number_of_philo)//вилок столько же сколько и философов
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL) != 0)
			return (ft_error("Mutex error"));
		i++;
	}
	return (0);
}

static int	check_fed_up(t_data *data)
{
	if (data->counter_times_eaten == data->number_of_philo)
	{
		pthread_mutex_lock(&data->print_lock);
		pthread_mutex_unlock(&data->breaker);
		return (1);
	}
	return (0);
}

static int	check_dead(t_data	*data, t_philo *philo, t_timeval time)
{
	if (get_time_in_ms(time) - get_time_in_ms(philo->last_eat)
		> (unsigned long)data->time_to_die)
	{
		pthread_mutex_lock(&data->print_lock);
		printf("%ld %d%s\n", get_cur_time(data), philo->index + 1, " died");
		return (1);
	}
	return (0);
}

void	finish_game(t_data *data)
{
	int				i;
	t_timeval		current;

	i = 0;
	usleep(200);
	while (1)
	{
		if (i == data->number_of_philo)
			i = 0;
		gettimeofday(&current, NULL);
		pthread_mutex_lock(&data->breaker);
		if (check_dead(data, &data->philo[i], current))
		{
			pthread_mutex_unlock(&data->breaker);
			break ;
		}
		if (check_fed_up(data) == 1)
			break ;
		pthread_mutex_unlock(&data->breaker);
		i++;
		usleep(200);
	}
}
