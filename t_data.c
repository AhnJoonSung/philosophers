/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_data.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahn <ahn@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 17:58:48 by ahn               #+#    #+#             */
/*   Updated: 2023/12/17 19:10:10 by ahn              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	return (data);
}

// return : malloc fail 시 NULL 반환
t_data	*new_data_init(\
int num_of_philo, int time_to_die, int time_to_eat, int time_to_sleep)
{
	t_data	*data;

	data = new_data();
	if (!data)
		return (0);
	data->num_of_philo = num_of_philo;
	data->time_to_die = time_to_die;
	data->time_to_eat = time_to_eat;
	data->time_to_sleep = time_to_sleep;
	return (data);
}