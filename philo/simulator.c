/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:32:43 by jooahn            #+#    #+#             */
/*   Updated: 2023/12/22 22:44:56 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	set_simulator(pthread_mutex_t **forks, t_data **data);
static int	create_threads(t_data *data, pthread_mutex_t *forks);
static void	clear_simulator(pthread_mutex_t *forks, int num_of_fork);

void	simulator(t_data *data)
{
	pthread_mutex_t	*forks;

	if (set_simulator(&forks, &data) != 0)
		return ;
	if (create_threads(data, forks) != 0)
		return ;
	while (1)
	{
		pthread_mutex_lock(data->end_mutex);
		if (data->is_end)
			break ;
		pthread_mutex_unlock(data->end_mutex);
	}
	pthread_mutex_unlock(data->end_mutex);
	clear_simulator(forks, data->num_of_philo);
}

static int	set_simulator(pthread_mutex_t **forks, t_data **data)
{
	*forks = set_forks((*data)->num_of_philo);
	if (!*forks)
		return (1);
	if (gettimeofday(&((*data)->start_tv), 0) != 0)
		return (1);
	return (0);
}

static int	create_threads(t_data *data, pthread_mutex_t *forks)
{
	pthread_t	*threads;
	t_philo		**philos;
	int			i;

	philos = set_philos(data, forks);
	if (!philos)
		return (1);
	threads = (pthread_t *)malloc(sizeof(pthread_t) * (data->num_of_philo + 2));
	if (!threads)
		return (1);
	i = 0;
	while (i < data->num_of_philo)
	{
		if (create_detach_thread(threads + i, philo, philos[i]) != 0)
			return (1);
		i++;
	}
	if (create_detach_thread(threads + i++, death_monitor, philos) != 0)
		return (1);
	if (create_detach_thread(threads + i, full_monitor, philos) != 0)
		return (1);
	return (0);
}

static void	clear_simulator(pthread_mutex_t *forks, int num_of_fork)
{
	int	i;

	i = 0;
	while (i < num_of_fork)
		pthread_mutex_destroy(forks + i++);
}
