/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:19:00 by jooahn            #+#    #+#             */
/*   Updated: 2024/01/05 17:28:29 by jooahn           ###   ########.fr       */
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
			return (FT_TRUE);
	}
	return (FT_FALSE);
}
