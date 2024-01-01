/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:32:10 by jooahn            #+#    #+#             */
/*   Updated: 2024/01/01 19:43:46 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// return milli seconds
long	get_time(t_timeval start_tv)
{
	return (get_utime(start_tv) / 1000);
}

// return micro seconds
long	get_utime(t_timeval start_tv)
{
	t_timeval	now_tv;
	long		sec;
	int			usec;
	const int	max_usec = 1000000;

	gettimeofday(&now_tv, 0);
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

void	busy_waiting(useconds_t usec)
{
	t_timeval	start_tv;

	gettimeofday(&start_tv, 0);
	while ((useconds_t)get_utime(start_tv) < usec)
		;
}
