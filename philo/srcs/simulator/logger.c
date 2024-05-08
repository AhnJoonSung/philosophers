/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:34:46 by jooahn            #+#    #+#             */
/*   Updated: 2024/01/15 15:38:23 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	*get_msg(int status);

void	logger(t_philo *philo, long time, int status)
{
	pthread_mutex_lock(philo->data->log_mutex);
	printf("%ld %d %s\n", time, philo->x, get_msg(status));
	pthread_mutex_unlock(philo->data->log_mutex);
}

int	safety_logger(t_philo *philo, long time, int status)
{
	pthread_mutex_lock(philo->data->end_mutex);
	if (philo->data->is_end)
	{
		pthread_mutex_unlock(philo->data->end_mutex);
		return (FT_FAIL);
	}
	pthread_mutex_lock(philo->data->log_mutex);
	printf("%ld %d %s\n", time, philo->x, get_msg(status));
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
