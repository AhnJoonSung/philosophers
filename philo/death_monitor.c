/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:21:51 by jooahn            #+#    #+#             */
/*   Updated: 2023/12/19 22:22:43 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	death_monitoring(t_data *data, t_philo **philos);
static int	is_philo_died(t_philo **philos, int i, t_data *data);

void	*death_monitor(void *arg)
{
	t_philo	**philos;
	t_data	*data;

	philos = (t_philo **)arg;
	data = (*philos)->data;
	while (1)
		if (death_monitoring(data, philos) != 0)
			return (0);
}

static int	death_monitoring(t_data *data, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_mutex_lock(data->end_mutex);
		if (data->is_end)
		{
			pthread_mutex_unlock(data->end_mutex);
			return (1);
		}
		if (is_philo_died(philos, i, data))
		{
			logger(get_time(data->start_tv), philos[i]->x, DIED, data);
			data->is_end = 1;
			pthread_mutex_unlock(data->end_mutex);
			return (1);
		}
		pthread_mutex_unlock(data->end_mutex);
		i++;
	}
	return (0);
}

static int	is_philo_died(t_philo **philos, int i, t_data *data)
{
	pthread_mutex_lock(philos[i]->last_eat_mutex);
	if (get_time(data->start_tv) - philos[i]->last_eat > data->time_to_die)
	{
		pthread_mutex_unlock(philos[i]->last_eat_mutex);
		return (1);
	}
	pthread_mutex_unlock(philos[i]->last_eat_mutex);
	return (0);
}
