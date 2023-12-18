/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahn <ahn@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:34:46 by jooahn            #+#    #+#             */
/*   Updated: 2023/12/17 19:28:57 by ahn              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static char	*get_msg(int code);

void logger(int time, int philo_num, int status)
{
	printf("%d %d", time, philo_num);
	printf("%s\n", get_msg(status));
}

static char	*get_msg(int code)
{
	if (code == TAKEN)
		return ("has taken a fork");
	if (code == EATING)
		return ("is eating");
	if (code == SLEEPING)
		return ("is sleeping");
	if (code == TAKEN)
		return ("is thinking");
	if (code == DIED)
		return ("died");
	return (0);
}