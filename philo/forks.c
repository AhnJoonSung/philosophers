/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 22:40:56 by jooahn            #+#    #+#             */
/*   Updated: 2024/01/05 21:23:52 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	take_fork(t_philo *philo, t_fork *fork);
static void	release_fork(t_fork *fork);

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

void	release_forks(t_philo *philo)
{
	release_fork(philo->main_fork);
	release_fork(philo->second_fork);
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
			fork->is_taken = FT_TRUE;
			pthread_mutex_unlock(&(fork->mutex));
			if (logger(philo, TAKEN) == FT_FAIL)
				return (FT_FAIL);
			return (FT_TRUE);
		}
		pthread_mutex_unlock(&(fork->mutex));
	}
}

static void	release_fork(t_fork *fork)
{
	pthread_mutex_lock(&(fork->mutex));
	fork->is_taken = FT_FALSE;
	pthread_mutex_unlock(&(fork->mutex));
}
