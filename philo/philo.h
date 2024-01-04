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

# define FT_CLEANUP_TIME 500000
# define FT_WAIT_TIME 1000
# define FT_ATOMIC_TIME 100

typedef struct timeval	t_timeval;

enum					e_status
{
	THINKING,
	TAKEN,
	EATING,
	SLEEPING,
	DIED,
	WAIT
};

typedef struct s_fork
{
	int					is_taken;
	pthread_mutex_t		fork_mutex;
}						t_fork;

typedef struct s_data
{
	int					num_of_philo;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				number_of_must_eat;
	int					is_end;
	pthread_mutex_t		*log_mutex;
	pthread_mutex_t		*end_mutex;
}						t_data;

typedef struct s_philo
{
	int					x;
	t_fork				*main_fork;
	t_fork				*second_fork;
	long				last_eat;
	long				remain_eating;
	t_data				*data;
	pthread_mutex_t		*last_eat_mutex;
	pthread_mutex_t		*remain_mutex;
}						t_philo;

int						is_natural_num(char *str);
int						get_isend(t_data *data);
long					ft_strtol(const char *str);
void					create_detach_thread(pthread_t *thread,
							void *(*f)(void *), void *arg);
long					get_time(void);
void					spend_time(t_data *data, int status);

void					logger(int philo_num, int status, t_data *data);

pthread_mutex_t			*new_mutex(void);
void					del_mutex(pthread_mutex_t *mutex);
t_data					*new_data(void);
void					del_data(t_data *data);
t_philo					*new_philo(void);

t_fork					*set_forks(int cnt);
void					take_forks(t_philo *philo);
void					release_forks(t_philo *philo);
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
