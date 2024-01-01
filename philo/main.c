/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahn <ahn@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:13:37 by jooahn            #+#    #+#             */
/*   Updated: 2023/12/31 20:16:38 by ahn              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;
	int		status;

	if (ac < 5 || ac > 6)
		return ;
	data = new_data();
	data->num_of_philo = ft_strtol(av[1]);
	data->time_to_die = ft_strtol(av[2]);
	data->time_to_eat = ft_strtol(av[3]);
	data->time_to_sleep = ft_strtol(av[4]);
	if (ac == 6)
		data->number_of_must_eat = ft_strtol(av[5]);
	simulator(data);
	return (0);
}
