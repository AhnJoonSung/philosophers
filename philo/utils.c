/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahn <ahn@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 22:39:41 by jooahn            #+#    #+#             */
/*   Updated: 2024/01/08 21:33:40 by ahn              ###   ########.fr       */
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
