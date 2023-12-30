/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:32:10 by jooahn            #+#    #+#             */
/*   Updated: 2023/12/31 05:48:47 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// return milli seconds
long	get_time(t_timeval start_tv)
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
	return (sec * 1000 + usec / 1000);
}
