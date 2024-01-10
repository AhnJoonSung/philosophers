/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:19:00 by jooahn            #+#    #+#             */
/*   Updated: 2024/01/10 18:08:51 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	find_died_philo(t_philo **philos, t_data *data);

void	*monitoring(void *arg)
{
	t_philo	**philos;

	philos = (t_philo **)arg;
	while (1)
	{
		if (get_end((*philos)->data))
			return (0);
		if (find_died_philo(philos, (*philos)->data))
			return (0);
	}
}

static t_bool	find_died_philo(t_philo **philos, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philo)
	{
		if (is_philo_died(philos[i]))
		{
			set_end(data);
			logger(philos[i], get_time(), DIED);
			return (FT_TRUE);
		}
	}
	return (FT_FALSE);
}
