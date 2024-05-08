/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_philo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 23:02:51 by jooahn            #+#    #+#             */
/*   Updated: 2024/01/10 22:58:19 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_philo_forks(t_philo *philo, t_fork *forks);
static void	del_philo(t_philo *philo);

t_philo	*new_philo(void)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (0);
	philo->last_eat = 0;
	philo->eat_cnt = 0;
	philo->mutex = new_mutex();
	return (philo);
}

t_philo	**set_philos(t_data *data, t_fork *forks)
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
		{
			clear_philos(philos, i - 1);
			return (0);
		}
		philos[i]->x = i + 1;
		philos[i]->data = data;
		set_philo_forks(philos[i], forks);
		i++;
	}
	return (philos);
}

static void	set_philo_forks(t_philo *philo, t_fork *forks)
{
	int	n;

	n = philo->data->num_of_philo;
	if (philo->x % 2 == 0)
	{
		philo->main_fork = forks + (philo->x - 1);
		philo->second_fork = forks + (philo->x % n);
	}
	else
	{
		philo->main_fork = forks + (philo->x % n);
		philo->second_fork = forks + (philo->x - 1);
	}
}

void	clear_philos(t_philo **philos, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (philos[i])
			del_philo(philos[i]);
		i++;
	}
	free(philos);
}

static void	del_philo(t_philo *philo)
{
	del_mutex(philo->mutex);
	free(philo);
}
