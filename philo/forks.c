/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 22:40:56 by jooahn            #+#    #+#             */
/*   Updated: 2024/01/04 04:08:37 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// success -> return (0);
t_fork	*set_forks(int cnt)
{
	t_fork	*forks;

	forks = (t_fork *)malloc(sizeof(t_fork) * cnt);
	if (!forks)
		return (0);
	while (cnt-- > 0)
	{
		forks[cnt].is_taken = 0;
		pthread_mutex_init(&(forks[cnt].fork_mutex), 0);
	}
	return (forks);
}

void	take_forks(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&(philo->main_fork->fork_mutex));
		if (philo->main_fork->is_taken != 1)
		{
			pthread_mutex_lock(&(philo->second_fork->fork_mutex));
			if (philo->second_fork->is_taken != 1)
				break ;
			pthread_mutex_unlock(&(philo->second_fork->fork_mutex));
		}
		pthread_mutex_unlock(&(philo->main_fork->fork_mutex));
		usleep(FT_ATOMIC_TIME);
	}
	philo->main_fork->is_taken = 1;
	philo->second_fork->is_taken = 1;
	pthread_mutex_unlock(&(philo->second_fork->fork_mutex));
	pthread_mutex_unlock(&(philo->main_fork->fork_mutex));
	pthread_mutex_lock(philo->data->end_mutex);
	if (philo->data->is_end != 1)
	{
		logger(philo->x, TAKEN, philo->data);
		logger(philo->x, TAKEN, philo->data);
	}
	pthread_mutex_unlock(philo->data->end_mutex);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_lock(&(philo->main_fork->fork_mutex));
	philo->main_fork->is_taken = 0;
	pthread_mutex_unlock(&(philo->main_fork->fork_mutex));
	pthread_mutex_lock(&(philo->second_fork->fork_mutex));
	philo->second_fork->is_taken = 0;
	pthread_mutex_unlock(&(philo->second_fork->fork_mutex));
}

void	clear_forks(t_fork *forks, int cnt)
{
	while (cnt-- > 0)
		pthread_mutex_destroy(&(forks[cnt].fork_mutex));
	free(forks);
}
