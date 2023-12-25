/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_data.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 17:58:48 by ahn               #+#    #+#             */
/*   Updated: 2023/12/19 16:12:13 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// return : malloc fail 시 NULL 반환
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
	data->number_of_must_eat = FT_INFINITE;
	data->is_end = 0;
	data->end_mutex = new_mutex();
	data->log_mutex = new_mutex();
	pthread_mutex_init(data->end_mutex, 0);
	pthread_mutex_init(data->log_mutex, 0);
	return (data);
}
