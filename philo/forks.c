/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahn <ahn@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 22:40:56 by jooahn            #+#    #+#             */
/*   Updated: 2023/12/31 19:37:20 by ahn              ###   ########.fr       */
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
		pthread_mutex_init(forks + cnt, 0);
	return (forks);
}

void	clear_forks(t_fork *forks, int cnt)
{
	while (cnt-- > 0)
		pthread_mutex_destroy(forks + cnt);
	free(forks);
}
