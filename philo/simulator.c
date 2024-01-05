/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:32:43 by jooahn            #+#    #+#             */
/*   Updated: 2024/01/05 22:32:20 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	set_simulator(t_data *data, t_fork **forks, t_philo ***philos);

void	simulator(t_data *data)
{
	t_fork		*forks;
	t_philo		**philos;
	pthread_t	*philo_threads;
	pthread_t	monitor_thread;
	int			i;

	if (set_simulator(data, &forks, &philos) != 0)
		return (clear_simulator(data, forks, philos, 1));
	pthread_create(&monitor_thread, 0, monitoring, philos);
	pthread_detach(monitor_thread);
	philo_threads = (pthread_t *)malloc(sizeof(pthread_t) * (data->num_of_philo));
	if (!philo_threads)
		return (clear_simulator(data, forks, philos, 0));
	create_philo_threads(data, philo_threads, philo, philos);
	i = -1;
	while (++i < data->num_of_philo)
		pthread_join(philo_threads[i], 0);
	free(philo_threads);
	clear_simulator(data, forks, philos, 0);
}

static int	set_simulator(t_data *data, t_fork **forks, t_philo ***philos)
{
	*forks = set_forks(data->num_of_philo);
	if (!*forks)
		return (1);
	*philos = set_philos(data, *forks);
	if (!*philos)
	{
		clear_forks(*forks, data->num_of_philo);
		return (1);
	}
	return (0);
}

void	clear_simulator(t_data *data, t_fork *forks, t_philo **philos,
		int status)
{
	if (status == 0)
	{
		clear_forks(forks, data->num_of_philo);
		clear_philos(philos, data->num_of_philo);
	}
	del_data(data);
}
