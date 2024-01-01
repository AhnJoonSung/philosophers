/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 22:40:56 by jooahn            #+#    #+#             */
/*   Updated: 2024/01/01 20:51:31 by jooahn           ###   ########.fr       */
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

void	take_fork(t_fork *fork)
{
	while (1)
	{
		pthread_mutex_lock(&(fork->fork_mutex));
		if (fork->is_taken)
		{
			pthread_mutex_unlock(&(fork->fork_mutex));
			continue ;
		}
		fork->is_taken = 1;
		pthread_mutex_unlock(&(fork->fork_mutex));
		return ;
	}
}

void	release_fork(t_fork *fork)
{
	pthread_mutex_lock(&(fork->fork_mutex));
	fork->is_taken = 0;
	pthread_mutex_unlock(&(fork->fork_mutex));
}

void	clear_forks(t_fork *forks, int cnt)
{
	while (cnt-- > 0)
		pthread_mutex_destroy(&(forks[cnt].fork_mutex));
	free(forks);
}
