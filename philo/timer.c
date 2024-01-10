/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:32:10 by jooahn            #+#    #+#             */
/*   Updated: 2024/01/10 18:37:54 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_timeval	*get_tv(void);

// return milli seconds
long	get_time(void)
{
	t_timeval			start;
	long				start_time;
	t_timeval			now;
	long				now_time;

	gettimeofday(&now, 0);
	start = *(get_tv());
	start_time = start.tv_sec * 1000 + start.tv_usec / 1000;
	now_time = now.tv_sec * 1000 + now.tv_usec / 1000;
	return (now_time - start_time);
}

void	set_timer(void)
{
	gettimeofday(get_tv(), 0);
}

static t_timeval	*get_tv(void)
{
	static t_timeval	tv;

	return (&tv);
}

void	spend_time(t_data *data, long start, int status)
{
	long	until;

	if (status == EATING)
		until = (start + data->time_to_eat);
	else if (status == SLEEPING)
		until = (start + data->time_to_sleep);
	else if (status == WAIT)
		until = start + data->time_to_eat - data->time_to_sleep + 2;
	else if (status == MONITORING)
		until = start + 5;
	else
		until = 0;
	while (get_time() < until)
		usleep(400);
}
