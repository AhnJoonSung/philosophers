/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:32:43 by jooahn            #+#    #+#             */
/*   Updated: 2024/01/04 23:22:42 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	set_simulator(t_data *data, t_fork **forks, t_philo ***philos);
static int	create_threads(t_data *data, t_philo **philos);

void	simulator(t_data *data)
{
	t_fork	*forks;
	t_philo	**philos;

	if (set_simulator(data, &forks, &philos) != 0)
		return (clear_simulator(data, forks, philos, 1));
	if (create_threads(data, philos) != 0)
		return (clear_simulator(data, forks, philos, 0));
	while (1)
	{
		if (get_isend(data))
			break ;
		usleep(FT_ATOMIC_TIME);
	}
	usleep(FT_CLEANUP_TIME);
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

static int	create_threads(t_data *data, t_philo **philos)
{
	pthread_t	*threads;
	int			i;
	int			n;

	n = data->num_of_philo;
	threads = (pthread_t *)malloc(sizeof(pthread_t) * (n + 2));
	if (!threads)
		return (1);
	create_detach_thread(threads + n, death_monitor, philos);
	if (data->number_of_must_eat != -1)
		create_detach_thread(threads + n + 1, full_monitor, philos);
	i = -1;
	while (++i < n)
		create_detach_thread(threads + i, philo, philos[i]);
	free(threads);
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
