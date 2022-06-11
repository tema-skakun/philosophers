/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 23:48:42 by fdarkhaw          #+#    #+#             */
/*   Updated: 2022/06/11 13:51:29 by fdarkhaw         ###   ########.fr       */
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
		if (pthread_create(&(data->philo[i].id), NULL, simulation,
				(void *)&(data->philo[i])))
			return (ft_error("Create error"));
		if (pthread_detach(data->philo[i].id) != 0)
			return (ft_error("Detach error"));
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
		return (ft_error("Wrong number of arguments"));
	if (validation(&data, av))//ok
		return (1);
	if (init_philosophers(&data) || init_forks(&data))
		return (1);
	if (start_game(&data))
		return (1);
	finish_game(&data);
	return (0);
}
