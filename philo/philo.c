/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:17:52 by jooahn            #+#    #+#             */
/*   Updated: 2023/12/22 22:58:04 by jooahn           ###   ########.fr       */
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
	if (get_is_end)
		return (1);
	logger(get_time(data->start_tv), philo->x, THINKING, data);
	return (0);
}

static int	taken(t_philo *philo, t_data *data)
{
	if (get_is_end)
		return (1);
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
	if (get_is_end)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	logger(get_time(data->start_tv), philo->x, TAKEN, data);
	return (0);
}

static int	eating(t_philo *philo, t_data *data)
{

}

static int	sleeping(t_philo *philo, t_data *data)
{

}

