/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahn <ahn@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:34:46 by jooahn            #+#    #+#             */
/*   Updated: 2024/01/08 21:26:50 by ahn              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	*get_msg(int status);

// 로그 실패시 FALSE 리턴
int	logger(t_philo *philo, int status)
{
	pthread_mutex_lock(philo->data->log_mutex);
	if (get_end(philo->data))
	{
		pthread_mutex_unlock(philo->data->log_mutex);
		return (FT_FAIL);
	}
	printf("%ld %d %s\n", get_time(), philo->x, get_msg(status));
	pthread_mutex_unlock(philo->data->log_mutex);
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
