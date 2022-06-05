/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 23:48:42 by ulagrezina        #+#    #+#             */
/*   Updated: 2022/06/05 23:28:29 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(int ms)
{
	struct timeval	start;
	struct timeval	now;

	gettimeofday(&start, 0);
	gettimeofday(&now, 0);
	while ((now.tv_sec - start.tv_sec) * 1000 + \
			(now.tv_usec - start.tv_usec) / 1000 < ms)
	{
		usleep(1);
		gettimeofday(&now, 0);
	}
}

void	*ft_run(void *data)
{
	t_data	*_data = data;
	pthread_mutex_lock(_data->p_mutex);//нужно сделать lock до обращения к переменной
	while (*(_data->num) < 10)
	{
		(*_data->num)++;
		pthread_mutex_unlock(_data->p_mutex);//нужно сделать unlock после обращения к переменной
		ft_usleep(100);
		pthread_mutex_lock(_data->p_mutex);//и опять lock для следующей операции
	}
	pthread_mutex_unlock(_data->p_mutex);//и опять unlock после последней операции
	return (0);
}

int	main(int argc, char **argv)
{
	pthread_t	id;
	void		*returned;
	int			tmp = 0;
	t_mutex		mutex;
	t_data		data;
	t_philo		philo;

	philo = (t_philo){};
	(void)argc;
	(void)argv;	
	validation_and_parcing(argc, argv, &philo);
	pthread_mutex_init(&philo.left, 0);//инициализация mutex по умолчанию
	pthread_mutex_init(&philo.right, 0);//инициализация mutex по умолчанию
	while (philo.num_of_philo)
	{
		pthread_create(id, 0, philosophers, &philo);
		philo.num_of_philo--;
	}
	data.p_mutex = &mutex;//будет защищать от гонки данных
	data.num = &tmp;
	printf("philo\t- %d %d %d %d\n", philo.num_of_philo, philo.time_to_die, philo.time_to_eat, philo.time_to_sleep);
	pthread_mutex_init(&mutex, 0);//инициализация mutex по умолчанию
	pthread_mutex_lock(&mutex);//нужно сделать lock до обращения к переменной
	pthread_create(&id, 0, ft_run, &data);//создал поток
	while (tmp < 10)
	{
		printf("%d\n", tmp);
		pthread_mutex_unlock(&mutex);//нужно сделать unlock после обращения к переменной
		ft_usleep(100);
		pthread_mutex_lock(&mutex);//и опять lock для следующей операции
	}
	pthread_mutex_unlock(&mutex);//и опять unlock после последней операции
	pthread_join(id, &returned);//главный поток будет ждать завершения второстепенного потока
	// pthread_detach(id);//отсоединяет второстепенный поток
	return (0);
}
