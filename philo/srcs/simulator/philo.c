/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:17:52 by jooahn            #+#    #+#             */
/*   Updated: 2024/01/11 15:22:21 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	thinking(t_philo *philo);
static int	taken(t_philo *philo);
static int	eating(t_philo *philo, t_data *data);
static int	sleeping(t_philo *philo);

void	*philo(void *arg)
{
	t_philo		*philo;
	t_data		*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (1)
	{
		if (thinking(philo) != FT_SUCCESS)
			return (0);
		if (taken(philo) != FT_SUCCESS)
			return (0);
		if (eating(philo, data) != FT_SUCCESS)
			return (0);
		if (sleeping(philo) != FT_SUCCESS)
			return (0);
		if (data->num_of_philo % 2 != 0)
			spend_time(data, get_time(), WAIT);
	}
	return (0);
}

static int	thinking(t_philo *philo)
{
	if (safety_logger(philo, get_time(), THINKING) != FT_SUCCESS)
		return (FT_FAIL);
	return (FT_SUCCESS);
}

static int	taken(t_philo *philo)
{
	if (take_forks(philo) != FT_SUCCESS)
		return (FT_FAIL);
	return (FT_SUCCESS);
}

static int	eating(t_philo *philo, t_data *data)
{
	long	start_time;

	start_time = get_time();
	pthread_mutex_lock(philo->mutex);
	philo->last_eat = start_time;
	pthread_mutex_unlock(philo->mutex);
	if (safety_logger(philo, start_time, EATING) != FT_SUCCESS)
	{
		release_forks(philo);
		return (FT_FAIL);
	}
	spend_time(data, start_time, EATING);
	if (++philo->eat_cnt == data->number_of_must_eat)
	{
		pthread_mutex_lock(data->full_mutex);
		if (++data->number_of_full == data->num_of_philo)
			set_end(data);
		pthread_mutex_unlock(data->full_mutex);
	}
	release_forks(philo);
	return (FT_SUCCESS);
}

static int	sleeping(t_philo *philo)
{
	long	start_time;

	start_time = get_time();
	if (safety_logger(philo, start_time, SLEEPING) != FT_SUCCESS)
		return (FT_FAIL);
	spend_time(philo->data, start_time, SLEEPING);
	return (FT_SUCCESS);
}
