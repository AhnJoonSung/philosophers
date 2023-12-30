/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:15:21 by jooahn            #+#    #+#             */
/*   Updated: 2023/12/18 23:59:09 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define FT_INFINITE 9223372036854775807L
# define FT_WAITTIME 500000

typedef struct timeval	t_timeval;
typedef pthread_mutex_t	t_fork;

enum	e_status
{
	THINKING,
	TAKEN,
	EATING,
	SLEEPING,
	DIED
};

typedef struct data
{
	long			num_of_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			number_of_must_eat;
	t_timeval		start_tv;
	int				is_end;
	pthread_mutex_t	*log_mutex;
	pthread_mutex_t	*end_mutex;
}					t_data;

typedef struct philo
{
	long			x;
	t_fork			*left_fork;
	t_fork			*right_fork;
	long			last_eat;
	long			remain_eating;
	t_data			*data;
	pthread_mutex_t	*last_eat_mutex;
	pthread_mutex_t	*remain_mutex;
}					t_philo;

pthread_mutex_t	*new_mutex(void);
void			del_mutex(pthread_mutex_t *mutex);
t_data			*new_data(void);
void			del_data(t_data *data);
t_philo			*new_philo(void);

long			get_time(t_timeval start_tv);
long			ft_strtol(const char *str);

pthread_mutex_t	*set_forks(int cnt);
void			clear_forks(pthread_mutex_t *forks, int cnt);
t_philo			**set_philos(t_data *data, pthread_mutex_t *forks);
void			clear_philos(t_philo **philos, int size);

int				create_detach_thread(\
pthread_t *thread, void *(*f)(void *), void *arg);

void			logger(long time, int philo_num, int status, t_data *data);

void			simulator(t_data *data);

void			*death_monitor(void *arg);
void			*full_monitor(void *arg);
void			*philo(void *arg);

int				is_philo_full(t_philo *philo);

#endif
