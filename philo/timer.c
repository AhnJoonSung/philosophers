/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:32:10 by jooahn            #+#    #+#             */
/*   Updated: 2024/01/03 22:05:02 by jooahn           ###   ########.fr       */
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
	t_timeval	start_tv;
	t_timeval	now_tv;
	long		sec;
	int			usec;
	const int	max_usec = 1000000;

	gettimeofday(&now_tv, 0);
	start_tv = *get_starttv();
	if (now_tv.tv_usec < start_tv.tv_usec)
	{
		sec = (now_tv.tv_sec - start_tv.tv_sec) - 1;
		usec = (max_usec - start_tv.tv_usec) + now_tv.tv_usec;
	}
	else
	{
		sec = now_tv.tv_sec - start_tv.tv_sec;
		usec = now_tv.tv_usec - start_tv.tv_usec;
	}
	return (sec * 1000000 + usec);
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

void	set_timer(void)
{
	gettimeofday(get_starttv(), 0);
}

t_timeval	*get_starttv(void)
{
	static t_timeval	tv;

	return (&tv);
}
