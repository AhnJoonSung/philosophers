/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_end.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 22:45:04 by jooahn            #+#    #+#             */
/*   Updated: 2023/12/22 22:49:44 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_is_end(t_data *data)
{
	pthread_mutex_lock(data->end_mutex);
	if (data->is_end)
	{
		pthread_mutex_unlock(data->end_mutex);
		return (1);
	}
	pthread_mutex_unlock(data->end_mutex);
}

void	set_is_end(t_data *data)
{
	pthread_mutex_lock(data->end_mutex);
	data->is_end = 1;
	pthread_mutex_unlock(data->end_mutex);
}
