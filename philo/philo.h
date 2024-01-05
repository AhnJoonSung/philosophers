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

# define FT_SUCCESS 1
# define FT_FAIL 0
# define FT_TRUE 1
# define FT_FALSE 0
# define FT_ATOMIC_TIME 200

typedef struct timeval	t_timeval;
typedef int				t_bool;

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
	t_bool				is_taken;
	pthread_mutex_t		mutex;
}						t_fork;

typedef struct s_data
{
	int					num_of_philo;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				number_of_must_eat;
	int					number_of_full;
	t_bool				is_end;
	pthread_mutex_t		*log_mutex;
	pthread_mutex_t		*end_mutex;
	pthread_mutex_t		*full_mutex;
}						t_data;

typedef struct s_philo
{
	int					x;
	t_fork				*main_fork;
	t_fork				*second_fork;
	long				last_eat;
	long				eat_cnt;
	t_data				*data;
	pthread_mutex_t		*mutex;
}						t_philo;

t_bool					get_end(t_data *data);
void					set_end(t_data *data);
int						is_natural_num(char *str);
long					ft_strtol(const char *str);
long					get_time(void);
t_bool					is_philo_died(t_philo *philo);
void					create_philo_threads(t_data *data, pthread_t *threads, void *(*philo)(void *), t_philo **philos);
void					spend_time(t_philo *philo, long start, int status);

int						logger(t_philo *philo, int status);

pthread_mutex_t			*new_mutex(void);
void					del_mutex(pthread_mutex_t *mutex);
t_data					*new_data(void);
void					del_data(t_data *data);
t_philo					*new_philo(void);

t_fork					*set_forks(int cnt);
t_bool					take_forks(t_philo *philo);
void					release_fork(t_fork *fork);
void					clear_forks(t_fork *forks, int cnt);
t_philo					**set_philos(t_data *data, t_fork *forks);
void					clear_philos(t_philo **philos, int size);

void					simulator(t_data *data);
void					*philo(void *arg);
void					*monitoring(void *arg);

void					clear_simulator(t_data *data, t_fork *forks,
							t_philo **philos, int status);

#endif
