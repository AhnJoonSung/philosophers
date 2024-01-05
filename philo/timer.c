/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:32:10 by jooahn            #+#    #+#             */
/*   Updated: 2024/01/05 22:03:30 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	return (get_utime() / 1000);
}

// return micro seconds
long	get_utime(void)
{
	static long			start_time;
	static t_timeval	start;
	t_timeval			now;
	long				now_time;

	if (start_time == 0)
	{
		gettimeofday(&start, 0);
		start_time = start.tv_sec * 1000000 + start.tv_usec;
	}
	gettimeofday(&now, 0);
	now_time = now.tv_sec * 1000000 + now.tv_usec;
	return (now_time - start_time);
}

void	spend_time(t_philo *philo, long start, int status)
{
	t_data	*data;
	long	until;
	long	gap_time;

	data = philo->data;
	until = 0;
	if (status == EATING)
		until = (start + data->time_to_eat);
	else if (status == SLEEPING)
		until = (start + data->time_to_sleep);
	else if (status == WAIT)
	{
		if (data->time_to_eat < data->time_to_sleep)
			return ;
		gap_time = data->time_to_eat - data->time_to_sleep;
		until = start + gap_time + 2;
	}
	until *= 1000;
	while (1)
	{
		if (is_philo_died(philo))
			return ;
		if (get_utime() >= until)
			return ;
		usleep(FT_ATOMIC_TIME);
	}
}
