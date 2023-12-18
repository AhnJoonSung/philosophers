/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahn <ahn@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:13:37 by jooahn            #+#    #+#             */
/*   Updated: 2023/12/17 21:31:40 by ahn              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*thread_func(void *arg)
{
	printf("hi %d\n", *(int *)arg);
	sleep(1);
	printf("bye\n");
	return (0);
}

int	main(int ac, char **av)
{
	t_data		*data;
	t_timeval	tv;
	int			ret;
	pthread_t	thread_id;
	int			value;

	value = 42;
	if (pthread_create(&thread_id, 0, thread_func, &value) != 0)
	{
		perror("create failed!\n");
		exit(1);
	}
	if (pthread_detach(thread_id) != 0)
	{
		perror("detach failed!\n");
		exit(1);
	}

	printf("I'm main thread!\n");
	// while (1)
	// {
	// 	ret = gettimeofday(&tv, 0);
	// 	if (ret == 0)
	// 		printf("%ld\n", tv.tv_sec);
	// 	sleep(1);
	// }
	if (ac == 5)
	{
		data = new_data();
		data->num_of_philo = ft_atoi(av[1]);
		data->time_to_die = ft_atoi(av[2]);
		data->time_to_eat = ft_atoi(av[3]);
		data->time_to_sleep = ft_atoi(av[4]);
		simulator(data);
	}
}
