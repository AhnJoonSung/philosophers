/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_monitor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 06:14:47 by jooahn            #+#    #+#             */
/*   Updated: 2024/01/04 22:59:11 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	full_monitoring(t_data *data, t_philo **philos);

void	*full_monitor(void *arg)
{
	t_philo	**philos;
	t_data	*data;

	philos = (t_philo **)arg;
	data = (*philos)->data;
	while (1)
	{
		if (get_isend(data))
			return (0);
		if (full_monitoring(data, philos) != 0)
			return (0);
	}
}

static int	full_monitoring(t_data *data, t_philo **philos)
{
	int	i;
	int	full_cnt;

	i = 0;
	full_cnt = 0;
	while (i < data->num_of_philo)
	{
		if (is_philo_full(philos[i++]))
		{
			if (++full_cnt == data->num_of_philo)
			{
				pthread_mutex_lock(data->end_mutex);
				data->is_end = 1;
				pthread_mutex_unlock(data->end_mutex);
				return (1);
			}
		}
	}
	return (0);
}

int	is_philo_full(t_philo *philo)
{
	int	is_full;

	is_full = 0;
	pthread_mutex_lock(philo->remain_mutex);
	if (philo->remain_eating == 0)
		is_full = 1;
	pthread_mutex_unlock(philo->remain_mutex);
	return (is_full);
}
