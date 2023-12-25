/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_philo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 23:02:51 by jooahn            #+#    #+#             */
/*   Updated: 2023/12/22 17:43:06 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*new_philo(void)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (0);
	philo->last_eat_mutex = new_mutex();
	philo->remain_mutex = new_mutex();
	pthread_mutex_init(philo->last_eat_mutex, 0);
	pthread_mutex_init(philo->remain_mutex, 0);
	return (philo);
}

t_philo	**set_philos(t_data *data, pthread_mutex_t *forks)
{
	t_philo	**philos;
	int		i;

	philos = (t_philo **)malloc(sizeof(t_philo *) * data->num_of_philo);
	if (!philos)
		return (0);
	i = 0;
	while (i < data->num_of_philo)
	{
		philos[i] = new_philo();
		if (!philos[i])
			return (0); // TO DO : 다 프리하고 리턴
		philos[i]->x = i;
		philos[i]->left_fork = forks + i;
		philos[i]->right_fork = forks + ((i + 1) % data->num_of_philo);
		philos[i]->last_eat = 0;
		philos[i]->remain_eating = data->number_of_must_eat;
		philos[i]->data = data;
		i++;
	}
	return (philos);
}
