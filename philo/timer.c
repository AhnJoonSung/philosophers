/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:32:10 by jooahn            #+#    #+#             */
/*   Updated: 2024/01/05 20:58:52 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// return milli seconds
long	get_time(void)
{
	static long			start_time;
	static t_timeval	start;
	t_timeval			now;
	long				now_time;

	if (start_time == 0)
	{
		gettimeofday(&start, 0);
		start_time = start.tv_sec * 1000 + start.tv_usec / 1000;
	}
	gettimeofday(&now, 0);
	now_time = now.tv_sec * 1000 + now.tv_usec / 1000;
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
	while (get_time() < until)
		usleep(FT_ATOMIC_TIME);
}
