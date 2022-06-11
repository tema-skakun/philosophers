/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 10:21:25 by fdarkhaw          #+#    #+#             */
/*   Updated: 2022/06/06 13:36:06 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

unsigned long	get_time(void)
{
	t_timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (ft_error("Time error"));
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	my_sleep(unsigned long ms)
{
	unsigned long	starttime;
	unsigned long	currenttime;

	starttime = get_time();
	currenttime = starttime;
	usleep(ms / 10 * 8);
	while (currenttime - starttime < ms)
	{
		currenttime = get_time();
		usleep(ms);
	}
}

unsigned long	get_time_in_ms(t_timeval time)
{
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

unsigned long	get_cur_time(t_data *sim)
{
	t_timeval	current;
	t_timeval	start;

	start = sim->start;
	gettimeofday(&current, NULL);
	return (get_time_in_ms(current) - get_time_in_ms(start));
}
