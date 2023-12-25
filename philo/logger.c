/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:34:46 by jooahn            #+#    #+#             */
/*   Updated: 2023/12/19 22:34:25 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	*get_msg(int code);

// philo_num + 1로 출력
void	logger(long time, int philo_num, int status, t_data *data)
{
	pthread_mutex_lock(data->log_mutex);
	printf("%ld %d ", time, philo_num + 1);
	printf("%s\n", get_msg(status));
	pthread_mutex_unlock(data->log_mutex);
}

static char	*get_msg(int code)
{
	if (code == TAKEN)
		return ("has taken a fork");
	if (code == EATING)
		return ("is eating");
	if (code == SLEEPING)
		return ("is sleeping");
	if (code == THINKING)
		return ("is thinking");
	if (code == DIED)
		return ("died");
	return (0);
}
