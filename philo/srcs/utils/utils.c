/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 22:39:41 by jooahn            #+#    #+#             */
/*   Updated: 2024/01/15 15:36:49 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_natural_num(char *str)
{
	t_bool	is_zero;

	is_zero = FT_TRUE;
	if (*str == '+')
		str++;
	while (*str)
	{
		if (*str < '0' || '9' < *str)
			return (0);
		if (*str != '0')
			is_zero = FT_FALSE;
		str++;
	}
	if (is_zero)
		return (0);
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

t_fork	*set_forks(int cnt)
{
	t_fork	*forks;

	forks = (t_fork *)malloc(sizeof(t_fork) * cnt);
	if (!forks)
		return (0);
	while (cnt-- > 0)
	{
		forks[cnt].is_taken = 0;
		pthread_mutex_init(&(forks[cnt].mutex), 0);
	}
	return (forks);
}

void	clear_forks(t_fork *forks, int cnt)
{
	while (cnt-- > 0)
		pthread_mutex_destroy(&(forks[cnt].mutex));
	free(forks);
}

void	create_philo_threads(t_data *data, pthread_t *threads,
							void *(*philo)(void *), t_philo **philos)
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
