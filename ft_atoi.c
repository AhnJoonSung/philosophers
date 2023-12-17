/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:23:43 by jooahn            #+#    #+#             */
/*   Updated: 2023/12/09 00:31:29 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isspace(int c);
static int	ft_isdigit(int c);

int	ft_atoi(char *str)
{
	int	i;
	int	num;
	int	sign;

	i = 0;
	num = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		sign = -1;
	while (ft_isdigit(str[i]))
	{
		num = (10 * num) + (str[i] - '0');
		i++;
	}
	return (sign * num);
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
