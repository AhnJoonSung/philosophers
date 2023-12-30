/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:17:52 by jooahn            #+#    #+#             */
/*   Updated: 2023/12/31 06:29:01 by jooahn           ###   ########.fr       */
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
	logger(get_time(data->start_tv), philo->x, THINKING, data);
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
	if (philo->x % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	pthread_mutex_lock(data->end_mutex);
	if (data->is_end)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(data->end_mutex);
		return (1);
	}
	logger(get_time(data->start_tv), philo->x, TAKEN, data);
	pthread_mutex_unlock(data->end_mutex);
	return (0);
}

static int	eating(t_philo *philo, t_data *data)
{
	long	eat_time;

	pthread_mutex_lock(data->end_mutex);
	if (data->is_end)
	{
		pthread_mutex_unlock(data->end_mutex);
		return (1);
	}
	eat_time = get_time(data->start_tv);
	logger(eat_time, philo->x, EATING, data);
	pthread_mutex_lock(philo->last_eat_mutex);
	philo->last_eat = eat_time;
	pthread_mutex_unlock(philo->last_eat_mutex);
	pthread_mutex_lock(philo->remain_mutex);
	philo->remain_eating--;
	pthread_mutex_unlock(philo->remain_mutex);
	pthread_mutex_unlock(data->end_mutex);
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

static int	sleeping(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(data->end_mutex);
	if (data->is_end)
	{
		pthread_mutex_unlock(data->end_mutex);
		return (1);
	}
	logger(get_time(data->start_tv), philo->x, SLEEPING, data);
	pthread_mutex_unlock(data->end_mutex);
	usleep(data->time_to_sleep * 1000);
	return (0);
}
