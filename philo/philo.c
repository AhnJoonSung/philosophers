/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:17:52 by jooahn            #+#    #+#             */
/*   Updated: 2024/01/05 00:53:46 by jooahn           ###   ########.fr       */
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
			spend_time(data, WAIT);
	}
	return (0);
}

static int	thinking(t_philo *philo, t_data *data)
{
	if (get_isend(data))
		return (1);
	logger(philo->x, THINKING, data);
	if (is_philo_full(philo))
		return (1);
	return (0);
}

static int	taken(t_philo *philo, t_data *data)
{
	if (get_isend(data))
		return (1);
	take_forks(philo);
	return (0);
}

static int	eating(t_philo *philo, t_data *data)
{
	long	now_time;

	if (get_isend(data))
	{
		release_forks(philo);
		return (1);
	}
	now_time = get_time();
	logger(philo->x, EATING, data);
	pthread_mutex_lock(philo->last_eat_mutex);
	philo->last_eat = now_time;
	pthread_mutex_unlock(philo->last_eat_mutex);
	spend_time(data, EATING);
	pthread_mutex_lock(philo->remain_mutex);
	if (philo->remain_eating > 0)
		philo->remain_eating--;
	pthread_mutex_unlock(philo->remain_mutex);
	release_forks(philo);
	return (0);
}

static int	sleeping(t_philo *philo, t_data *data)
{
	if (get_isend(data))
		return (1);
	logger(philo->x, SLEEPING, data);
	spend_time(data, SLEEPING);
	return (0);
}
