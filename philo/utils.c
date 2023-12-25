/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 22:39:41 by jooahn            #+#    #+#             */
/*   Updated: 2023/12/22 22:40:09 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_detach_thread(pthread_t *thread, void *(*f)(void *), void *arg)
{
	if (pthread_create(thread, 0, f, arg) != 0)
		return (1);
	if (pthread_detach(*thread) != 0)
		return (1);
	return (0);
}
