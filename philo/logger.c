/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:34:46 by jooahn            #+#    #+#             */
/*   Updated: 2024/01/05 01:47:12 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	*get_msg(int status);

// 로그 실패시 FALSE 리턴
int	logger(t_philo *philo, int status)
{
	pthread_mutex_lock(philo->data->end_mutex);
	if (philo->data->is_end)
	{
		pthread_mutex_unlock(philo->data->end_mutex);
		return (FT_FAIL);
	}
	pthread_mutex_lock(philo->data->log_mutex);
	printf("%ld %d ", get_time(), philo->x);
	printf("%s\n", get_msg(status));
	pthread_mutex_unlock(philo->data->log_mutex);
	pthread_mutex_unlock(philo->data->end_mutex);
	return (FT_SUCCESS);
}

static char	*get_msg(int status)
{
	if (status == TAKEN)
		return ("has taken a fork");
	if (status == EATING)
		return ("is eating");
	if (status == SLEEPING)
		return ("is sleeping");
	if (status == THINKING)
		return ("is thinking");
	if (status == DIED)
		return ("died");
	return (0);
}
