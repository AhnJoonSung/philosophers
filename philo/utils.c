/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 22:39:41 by jooahn            #+#    #+#             */
/*   Updated: 2024/01/05 22:21:05 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_philo_threads(t_data *data, pthread_t *threads, void *(*philo)(void *), t_philo **philos)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_create(threads + i, 0, philo, philos[i]);
		i += 2;
	}
	usleep(1000);
	i = 1;
	while (i < data->num_of_philo)
	{
		pthread_create(threads + i, 0, philo, philos[i]);
		i += 2;
	}
}

t_bool	is_philo_died(t_philo *philo)
{
	long	hungry_time;

	hungry_time = get_time() - philo->last_eat;
	if (hungry_time > philo->data->time_to_die)
	{
		pthread_mutex_lock(philo->data->end_mutex);
		if (philo->data->is_end)
		{
			pthread_mutex_unlock(philo->data->end_mutex);
			return (FT_TRUE);
		}
		printf("%ld %d died\n", get_time(), philo->x);
		philo->data->is_end = 1;
		pthread_mutex_unlock(philo->data->end_mutex);
		return (FT_TRUE);
	}
	return (FT_FALSE);
}

int	is_natural_num(char *str)
{
	if (*str == '+')
		str++;
	while (*str)
	{
		if (*str < '0' || '9' < *str)
			return (0);
		str++;
	}
	return (1);
}

long	ft_strtol(const char *str)
{
	long		num;
	long		cutoff;
	char		cutlim;
	const long	long_max = 9223372036854775807L;

	if (*str == '+')
		str++;
	num = 0;
	cutoff = long_max / 10;
	cutlim = long_max % 10 + '0';
	while (*str)
	{
		if ((num > cutoff) || (num == cutoff && *str > cutlim))
			return (long_max);
		num = (num * 10) + (*str - '0');
		str++;
	}
	return (num);
}
