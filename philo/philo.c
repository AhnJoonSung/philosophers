/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:17:52 by jooahn            #+#    #+#             */
/*   Updated: 2024/01/05 16:49:54 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	thinking(t_philo *philo);
static int	taken(t_philo *philo);
static int	eating(t_philo *philo);
static int	sleeping(t_philo *philo);

void	*philo(void *arg)
{
	t_philo		*philo;
	t_data		*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->x % 2 == 1)
		spend_time(philo, 0, EATING);
	while (1)
	{
		if (thinking(philo) == FT_FAIL)
			return (0);
		if (taken(philo) == FT_FAIL)
			return (0);
		if (eating(philo) == FT_FAIL)
			return (0);
		if (sleeping(philo) == FT_FAIL)
			return (0);
		if (data->num_of_philo % 2 == 1)
			spend_time(philo, get_time(), WAIT);
	}
	return (0);
}

static int	thinking(t_philo *philo)
{
	if (logger(philo, THINKING) == FT_FAIL)
		return (FT_FAIL);
	return (FT_SUCCESS);
}

static int	taken(t_philo *philo)
{
	if (take_forks(philo) == FT_FAIL)
		return (FT_FAIL);
	return (FT_SUCCESS);
}

static int	eating(t_philo *philo)
{
	long	now_time;
	t_data	*data;

	now_time = get_time();
	data = philo->data;
	philo->last_eat = now_time;
	if (logger(philo, EATING) == FT_FAIL)
	{
		release_forks(philo);
		return (FT_FAIL);
	}
	spend_time(philo, now_time, EATING);
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
	if (logger(philo, SLEEPING) == FT_FAIL)
		return (FT_FAIL);
	spend_time(philo, get_time(), SLEEPING);
	return (FT_SUCCESS);
}
