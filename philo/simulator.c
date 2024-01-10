/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:32:43 by jooahn            #+#    #+#             */
/*   Updated: 2024/01/10 23:41:55 by jooahn           ###   ########.fr       */
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
	int			n;

	if (set_simulator(data, &forks, &philos) != 0)
		return (clear_simulator(data, forks, philos, 1));
	pthread_create(&monitor_thread, 0, monitoring, philos);
	pthread_detach(monitor_thread);
	n = data->num_of_philo;
	philo_threads = (pthread_t *)malloc(sizeof(pthread_t) * n);
	if (!philo_threads)
		return (clear_simulator(data, forks, philos, 0));
	create_philo_threads(data, philo_threads, philo, philos);
	while (n -- > 0)
		pthread_join(philo_threads[n], 0);
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
	set_timer();
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
