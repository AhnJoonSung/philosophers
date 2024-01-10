/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:13:37 by jooahn            #+#    #+#             */
/*   Updated: 2024/01/10 18:42:39 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_args(int ac, char **av);

void test(void)
{
	system("leaks philo");
}

int	main(int ac, char **av)
{
	t_data	*data;

	atexit(test);
	if (check_args(ac, av) != 0)
	{
		printf("Invalid arguments.\n");
		return (0);
	}
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

static int	check_args(int ac, char **av)
{
	if (ac < 5 || 6 < ac)
		return (1);
	if (!is_natural_num(av[1]) || ft_strtol(av[1]) == 0)
		return (1);
	if (!is_natural_num(av[2]))
		return (1);
	if (!is_natural_num(av[3]))
		return (1);
	if (!is_natural_num(av[4]))
		return (1);
	if (ft_strtol(av[3]) == 0 || ft_strtol(av[4]) == 0)
		return (1);
	if (ac == 6 && !is_natural_num(av[5]))
		return (1);
	return (0);
}
