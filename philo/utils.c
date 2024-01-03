/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 22:39:41 by jooahn            #+#    #+#             */
/*   Updated: 2024/01/03 21:34:52 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	get_num(const char *str, int neg);

void	create_detach_thread(pthread_t *thread, void *(*f)(void *), void *arg)
{
	pthread_create(thread, 0, f, arg);
	pthread_detach(*thread);
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
	int	neg;

	neg = 0;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		neg = 1;
		str++;
	}
	return (get_num(str, neg));
}

static long	get_num(const char *str, int neg)
{
	long		num;
	long		cutoff;
	char		cutlim;
	const long	long_max = 9223372036854775807L;
	const long	long_min = -long_max - 1;

	num = 0;
	cutoff = long_max / 10;
	cutlim = long_max % 10 + '0';
	while (*str)
	{
		if ((num > cutoff) || (num == cutoff && *str > cutlim))
		{
			if (neg)
				return (long_min);
			return (long_max);
		}
		num = (num * 10) + (*str - '0');
		str++;
	}
	if (neg)
		return (-num);
	return (num);
}
