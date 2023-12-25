/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:49:27 by jooahn            #+#    #+#             */
/*   Updated: 2023/12/19 19:52:55 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isspace(int c);
static int	ft_isdigit(int c);
static long	get_num(const char *str, int neg);

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
	long	num;
	long	cutoff;
	char	cutlim;
	const long	LONG_MAX = 9223372036854775807L;
	const long	LONG_MIN = -LONG_MAX - 1;

	num = 0;
	cutoff = LONG_MAX / 10;
	cutlim = LONG_MAX % 10 + '0';
	while (ft_isdigit(*str))
	{
		if ((num > cutoff) || (num == cutoff && *str > cutlim))
		{
			if (neg)
				return (LONG_MIN);
			return (LONG_MAX);
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

