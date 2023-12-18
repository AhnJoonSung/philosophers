/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahn <ahn@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:15:21 by jooahn            #+#    #+#             */
/*   Updated: 2023/12/17 21:23:25 by ahn              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct timeval t_timeval;

enum	Status
{
	TAKEN,
	EATING,
	SLEEPING,
	THINKING,
	DIED
};

typedef struct data
{
	int	num_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
}		t_data;

void	simulator(t_data *data);
int		ft_atoi(char *str);

t_data	*new_data(void);
t_data	*new_data_init(\
int num_of_philo, int time_to_die, int time_to_eat, int time_to_sleep);

#endif
