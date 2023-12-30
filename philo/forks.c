/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 22:40:56 by jooahn            #+#    #+#             */
/*   Updated: 2023/12/31 04:23:21 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// success -> return (0);
pthread_mutex_t	*set_forks(int cnt)
{
	pthread_mutex_t	*forks;

	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * cnt);
	if (!forks)
		return (0);
	while (cnt-- > 0)
	{
		if (pthread_mutex_init(forks + cnt, 0) != 0)
			return (0);
	}
	return (forks);
}

void	clear_forks(pthread_mutex_t *forks, int cnt)
{
	while (cnt-- > 0)
		pthread_mutex_destroy(forks + cnt);
	free(forks);
}
