/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 01:15:45 by fdarkhaw          #+#    #+#             */
/*   Updated: 2022/06/11 20:32:17 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (0);
	return (1);
}

int	check_parameteres(t_data *data)
{
	if (data->number_of_philo < 1 || data->number_of_philo > 200 || \
	data->time_to_die < 1 || data->time_to_eat < 1 || \
	data->time_to_sleep < 1)
		return (ft_error("you have passed an incorrect parameter(s)"));
	return (0);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while ((*str == ' ') || (*str == '\n') || (*str == '\t') || \
			(*str == '\v') || (*str == '\f') || (*str == '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = (result * 10) + (*str - '0');
		str++;
		if (result * sign > 0 && sign == -1)
			return (0);
		if (result * sign < 0 && sign == 1)
			return (-1);
	}
	return (result * sign);
}

int	fill_parameteres(t_data *data, char **av)
{
	data->number_of_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
	{
		data->number_of_times = ft_atoi(av[5]);
		if (data->number_of_times < 1)
			return (ft_error("you have passed an incorrect parameter(s)"));
	}
	else
		data->number_of_times = -1;
	data->counter_times_eaten = 0;
	return (check_parameteres(data));
}

int	validation(t_data *data, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (ft_isdigit(av[i][j]))
				return (ft_error("you have passed an incorrect parameter(s)"));
			j++;
		}
		i++;
	}
	return (fill_parameteres(data, av));
}
