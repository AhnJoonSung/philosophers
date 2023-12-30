/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 22:39:41 by jooahn            #+#    #+#             */
/*   Updated: 2023/12/31 06:00:35 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isspace(int c);
static int	ft_isdigit(int c);
static long	get_num(const char *str, int neg);

int	create_detach_thread(pthread_t *thread, void *(*f)(void *), void *arg)
{
	if (pthread_create(thread, 0, f, arg) != 0)
		return (1);
	if (pthread_detach(*thread) != 0)
		return (1);
	return (0);
}

long	ft_strtol(const char *str)
{
	int	neg;

	neg = 0;
	while (ft_isspace(*str))
		str++;
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
	while (ft_isdigit(*str))
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

static int	ft_isspace(int c)
{
	if (c == ' ' || ('\t' <= c && c <= '\r'))
		return (1);
	return (0);
}

static int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}
