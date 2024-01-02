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
# define FT_CLEANUP_TIME 500000
# define FT_WAIT_TIME 2000
# define FT_SWITCHING_TIME 2000

typedef struct timeval	t_timeval;

enum					e_status
{
	THINKING,
	TAKEN,
	EATING,
	SLEEPING,
	DIED
};

typedef struct fork
{
	int					is_taken;
	pthread_mutex_t		fork_mutex;
}						t_fork;

typedef struct data
{
	int					num_of_philo;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				number_of_must_eat;
	long				cnt;
	t_timeval			start_tv;
	int					is_end;
	pthread_mutex_t		*log_mutex;
	pthread_mutex_t		*end_mutex;
}						t_data;

typedef struct philo
{
	int					x;
	t_fork				*left_fork;
	t_fork				*right_fork;
	long				last_eat;
	long				remain_eating;
	t_data				*data;
	pthread_mutex_t		*last_eat_mutex;
	pthread_mutex_t		*remain_mutex;
}						t_philo;

int						is_natural_num(char *str);
long					ft_strtol(const char *str);
void					create_detach_thread(pthread_t *thread,
							void *(*f)(void *), void *arg);
void					ft_usleep(useconds_t usec);
long					get_time(t_timeval start_tv);
long					get_utime(t_timeval start_tv);

void					logger(long time, int philo_num, int status,
							t_data *data);

pthread_mutex_t 		*new_mutex(void);
void					del_mutex(pthread_mutex_t *mutex);
t_data					*new_data(void);
void					del_data(t_data *data);
t_philo					*new_philo(void);

t_fork					*set_forks(int cnt);
void					take_fork(t_philo *philo);
void					release_fork(t_fork *fork);
void					clear_forks(t_fork *forks, int cnt);
t_philo					**set_philos(t_data *data, t_fork *forks);
void					clear_philos(t_philo **philos, int size);

void					simulator(t_data *data);

void					*death_monitor(void *arg);
void					*full_monitor(void *arg);
int						is_philo_full(t_philo *philo);
void					*philo(void *arg);

void					clear_simulator(t_data *data, t_fork *forks,
							t_philo **philos, int status);

#endif
