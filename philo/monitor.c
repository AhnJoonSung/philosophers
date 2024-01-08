/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahn <ahn@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:19:00 by jooahn            #+#    #+#             */
/*   Updated: 2024/01/08 21:43:58 by ahn              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	find_died_philo(t_philo **philos, t_data *data);
static t_bool	is_philo_died(t_philo *philo);

void	*monitoring(void *arg)
{
	t_philo	**philos;
	long	start_time;

	philos = (t_philo **)arg;
	while (1)
	{
		start_time = get_time();
		if (find_died_philo(philos, (*philos)->data))
			return (0);
		spend_time((*philos)->data, start_time, MONITORING);
	}
}

static t_bool	find_died_philo(t_philo **philos, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philo)
	{
		if (is_philo_died(philos[i]))
			return (FT_TRUE);
	}
	return (FT_FALSE);
}

static t_bool	is_philo_died(t_philo *philo)
{
	long hungry_time;

	pthread_mutex_lock(philo->mutex);
	hungry_time = get_time() - philo->last_eat;
	pthread_mutex_unlock(philo->mutex);
	if (hungry_time > philo->data->time_to_die)
	{
		pthread_mutex_lock(philo->data->log_mutex);
		pthread_mutex_lock(philo->data->end_mutex);
		if (philo->data->is_end)
		{
			pthread_mutex_unlock(philo->data->log_mutex);
			pthread_mutex_unlock(philo->data->end_mutex);
			return (FT_TRUE);
		}
		printf("%ld %d died\n", get_time(), philo->x);
		pthread_mutex_unlock(philo->data->log_mutex);
		philo->data->is_end = 1;
		pthread_mutex_unlock(philo->data->end_mutex);
		return (FT_TRUE);
	}
	return (FT_FALSE);
}