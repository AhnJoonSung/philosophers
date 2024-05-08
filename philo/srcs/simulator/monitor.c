/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:19:00 by jooahn            #+#    #+#             */
/*   Updated: 2024/01/11 15:01:51 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	find_died_philo(t_philo **philos, t_data *data);
static t_bool	is_philo_died(t_philo *philo, long now_time);

void	*monitoring(void *arg)
{
	t_philo	**philos;

	philos = (t_philo **)arg;
	while (1)
	{
		if (get_end((*philos)->data))
			return (0);
		if (find_died_philo(philos, (*philos)->data))
			return (0);
		usleep(200);
	}
}

static t_bool	find_died_philo(t_philo **philos, t_data *data)
{
	int		i;
	long	now_time;

	i = -1;
	while (++i < data->num_of_philo)
	{
		now_time = get_time();
		if (is_philo_died(philos[i], now_time))
		{
			set_end(data);
			logger(philos[i], now_time, DIED);
			return (FT_TRUE);
		}
	}
	return (FT_FALSE);
}

static t_bool	is_philo_died(t_philo *philo, long now_time)
{
	long	hungry_time;

	pthread_mutex_lock(philo->mutex);
	hungry_time = now_time - philo->last_eat;
	pthread_mutex_unlock(philo->mutex);
	if (hungry_time > philo->data->time_to_die)
	{
		set_end(philo->data);
		return (FT_TRUE);
	}
	return (FT_FALSE);
}
