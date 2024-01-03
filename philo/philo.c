/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:17:52 by jooahn            #+#    #+#             */
/*   Updated: 2024/01/04 04:11:14 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	thinking(t_philo *philo, t_data *data);
static int	taken(t_philo *philo, t_data *data);
static int	eating(t_philo *philo, t_data *data);
static int	sleeping(t_philo *philo, t_data *data);

void	*philo(void *arg)
{
	t_philo		*philo;
	t_data		*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (1)
	{
		if (thinking(philo, data) != 0)
			return (0);
		if (taken(philo, data) != 0)
			return (0);
		if (eating(philo, data) != 0)
			return (0);
		if (sleeping(philo, data) != 0)
			return (0);
		if (data->num_of_philo % 2 == 1)
			spend_time(data, get_time(), WAIT);
	}
	return (0);
}

static int	thinking(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(data->end_mutex);
	if (data->is_end)
	{
		pthread_mutex_unlock(data->end_mutex);
		return (1);
	}
	logger(philo->x, THINKING, data);
	if (is_philo_full(philo))
	{
		pthread_mutex_unlock(data->end_mutex);
		return (1);
	}
	pthread_mutex_unlock(data->end_mutex);
	return (0);
}

static int	taken(t_philo *philo, t_data *data)
{
	take_forks(philo);
	pthread_mutex_lock(data->end_mutex);
	if (data->is_end)
	{
		release_forks(philo);
		pthread_mutex_unlock(data->end_mutex);
		return (1);
	}
	pthread_mutex_unlock(data->end_mutex);
	return (0);
}

static int	eating(t_philo *philo, t_data *data)
{
	long	now_time;

	now_time = get_time();
	pthread_mutex_lock(data->end_mutex);
	if (data->is_end)
	{
		release_forks(philo);
		pthread_mutex_unlock(data->end_mutex);
		return (1);
	}
	pthread_mutex_lock(philo->last_eat_mutex);
	philo->last_eat = now_time;
	pthread_mutex_unlock(philo->last_eat_mutex);
	pthread_mutex_lock(philo->remain_mutex);
	if (philo->remain_eating > 0)
		philo->remain_eating--;
	pthread_mutex_unlock(philo->remain_mutex);
	logger(philo->x, EATING, data);
	pthread_mutex_unlock(data->end_mutex);
	spend_time(data, now_time, EATING);
	release_forks(philo);
	return (0);
}

static int	sleeping(t_philo *philo, t_data *data)
{
	long	now_time;

	now_time = get_time();
	pthread_mutex_lock(data->end_mutex);
	if (data->is_end)
	{
		pthread_mutex_unlock(data->end_mutex);
		return (1);
	}
	logger(philo->x, SLEEPING, data);
	pthread_mutex_unlock(data->end_mutex);
	spend_time(data, now_time, SLEEPING);
	return (0);
}
