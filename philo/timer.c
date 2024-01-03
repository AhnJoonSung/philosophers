/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:32:10 by jooahn            #+#    #+#             */
/*   Updated: 2024/01/04 04:02:19 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// return milli seconds
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
	now_time = now.tv_sec * 1000000 + now.tv_usec - start_time;
	return (now_time);
}

// micro seconds
void	spend_time(t_data *data, long start, int status)
{
	long	until;
	long	gap_time;

	if (status == EATING)
		until = (start + data->time_to_eat) * 1000;
	else if (status == SLEEPING)
		until = (start + data->time_to_sleep) * 1000;
	else if (status == WAIT)
	{
		if (data->time_to_eat < data->time_to_sleep)
			return ;
		gap_time = data->time_to_eat - data->time_to_sleep;
		until = (start + gap_time) * 1000 + FT_WAIT_TIME;
	}
	else
		until = 0;
	while (get_utime() + FT_ATOMIC_TIME / 2 < until)
		usleep(FT_ATOMIC_TIME);
}
