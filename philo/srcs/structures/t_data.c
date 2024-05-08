/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_data.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 17:58:48 by ahn               #+#    #+#             */
/*   Updated: 2024/01/15 15:37:10 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*new_data(void)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (0);
	data->num_of_philo = 0;
	data->time_to_die = 0;
	data->time_to_eat = 0;
	data->time_to_sleep = 0;
	data->number_of_must_eat = -1;
	data->number_of_full = 0;
	data->is_end = FT_FALSE;
	data->end_mutex = new_mutex();
	data->log_mutex = new_mutex();
	data->full_mutex = new_mutex();
	return (data);
}

void	del_data(t_data *data)
{
	del_mutex(data->end_mutex);
	del_mutex(data->log_mutex);
	del_mutex(data->full_mutex);
	free(data);
}
