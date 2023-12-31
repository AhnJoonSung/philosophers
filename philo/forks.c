/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 22:40:56 by jooahn            #+#    #+#             */
/*   Updated: 2024/01/05 22:08:45 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	take_fork(t_philo *philo, t_fork *fork);

// 성공시 SUCCESS, 실패시 FAIL 반환
t_bool	take_forks(t_philo *philo)
{
	if (take_fork(philo, philo->main_fork) == FT_FAIL)
		return (FT_FAIL);
	if (take_fork(philo, philo->second_fork) == FT_FAIL)
	{
		release_fork(philo->main_fork);
		return (FT_FAIL);
	}
	return (FT_SUCCESS);
}

static t_bool	take_fork(t_philo *philo, t_fork *fork)
{
	while (1)
	{
		if (is_philo_died(philo))
			return (FT_FAIL);
		pthread_mutex_lock(&(fork->mutex));
		if (fork->is_taken == FT_FALSE)
		{
			if (logger(philo, TAKEN) == FT_FAIL)
			{
				pthread_mutex_unlock(&(fork->mutex));
				return (FT_FAIL);
			}
			fork->is_taken = FT_TRUE;
			pthread_mutex_unlock(&(fork->mutex));
			return (FT_TRUE);
		}
		pthread_mutex_unlock(&(fork->mutex));
	}
}

void	release_fork(t_fork *fork)
{
	pthread_mutex_lock(&(fork->mutex));
	fork->is_taken = FT_FALSE;
	pthread_mutex_unlock(&(fork->mutex));
}

t_fork	*set_forks(int cnt)
{
	t_fork	*forks;

	forks = (t_fork *)malloc(sizeof(t_fork) * cnt);
	if (!forks)
		return (0);
	while (cnt-- > 0)
	{
		forks[cnt].is_taken = 0;
		pthread_mutex_init(&(forks[cnt].mutex), 0);
	}
	return (forks);
}

void	clear_forks(t_fork *forks, int cnt)
{
	while (cnt-- > 0)
		pthread_mutex_destroy(&(forks[cnt].mutex));
	free(forks);
}
