/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:34:46 by jooahn            #+#    #+#             */
/*   Updated: 2024/01/03 21:29:45 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	*get_msg(int status);

// philo_num + 1로 출력
void	logger(long time, int philo_num, int status, t_data *data)
{
	pthread_mutex_lock(data->log_mutex);
	printf("%ld %d ", time, philo_num + 1);
	printf("%s\n", get_msg(status));
	pthread_mutex_unlock(data->log_mutex);
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
