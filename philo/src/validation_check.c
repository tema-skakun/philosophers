/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 20:05:41 by fdarkhaw          #+#    #+#             */
/*   Updated: 2022/06/05 23:08:07 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	res;
	int	neg;

	res = 0;
	neg = 1;
	while ((*str == ' ') || (*str == '\n') || (*str == '\t') \
			|| (*str == '\v') || (*str == '\f') || (*str == '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			neg = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = (res * 10) + (*str - '0');
		str++;
		if (res * neg > 0 && neg == -1)
			return (0);
		if (res * neg < 0 && neg == 1)
			return (-1);
	}
	return (res * neg);
}

int	validation(int ac, char **av)
{
	(void)av;
	if (ac < 5 || ac > 6)
	{
		printf("incorrect number of variables\n");
		return (1);
	}
	return (0);
}

void	parcing(char **av, t_philo *philo)
{
	philo->num_of_philo = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]) * 1000;
	philo->time_to_eat = ft_atoi(av[3]) * 1000;
	philo->time_to_sleep = ft_atoi(av[4]) * 1000;
	if (av[5])
		philo->num_of_times = ft_atoi(av[5]);
}

void	validation_and_parcing(int ac, char **av, t_philo *philo)
{
	if (!validation(ac, av))
		parcing(av, philo);
}
