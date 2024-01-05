/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 01:07:02 by jooahn            #+#    #+#             */
/*   Updated: 2024/01/05 01:09:31 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	get_end(t_data *data)
{
	int	res;

	pthread_mutex_lock(data->end_mutex);
	res = data->is_end;
	pthread_mutex_unlock(data->end_mutex);
	return (res);
}

void	set_end(t_data *data)
{
	pthread_mutex_lock(data->end_mutex);
	data->is_end = FT_TRUE;
	pthread_mutex_unlock(data->end_mutex);
}
