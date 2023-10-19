/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 23:48:42 by fdarkhaw          #+#    #+#             */
/*   Updated: 2022/06/12 12:47:18 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_error(char *msg)
{
	printf("Error: %s\n", msg);
	return (1);
}

int	start_game(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		if (pthread_create(&(data->philo[i].id), NULL, simulation, \
				(void *)&(data->philo[i])))
			return (ft_error("Create error"));
		if (pthread_detach(data->philo[i].id))
			return (ft_error("Detach error"));
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
		return (ft_error("Wrong number of arguments.\nProgram take the following arguments: number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]"));
	if (validation(&data, av))//ok
		return (1);
	if (init_philosophers(&data) || init_forks(&data))//ok
		return (1);
	if (start_game(&data))//ok
		return (1);
	finish_game(&data);
	return (0);
}
