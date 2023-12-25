/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:32:10 by jooahn            #+#    #+#             */
/*   Updated: 2023/12/19 17:35:43 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// return milli seconds
long	get_time(t_timeval start_tv)
{
	t_timeval	now_tv;
	long		sec;
	long		usec;

	gettimeofday(&now_tv, 0);
	sec = now_tv.tv_sec - start_tv.tv_sec;
	usec = now_tv.tv_usec - start_tv.tv_usec;
	return (sec * 1000 + usec / 1000);
}
