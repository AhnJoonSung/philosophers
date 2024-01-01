/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:13:37 by jooahn            #+#    #+#             */
/*   Updated: 2024/01/01 20:36:51 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac < 5 || ac > 6)
		return (0);
	data = new_data();
	data->num_of_philo = (int)ft_strtol(av[1]);
	data->time_to_die = ft_strtol(av[2]);
	data->time_to_eat = ft_strtol(av[3]);
	data->time_to_sleep = ft_strtol(av[4]);
	if (ac == 6)
		data->number_of_must_eat = ft_strtol(av[5]);
	simulator(data);
	return (0);
}
