/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:02:00 by yrio              #+#    #+#             */
/*   Updated: 2024/10/15 15:07:38 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

#define NC	"\e[0m"
#define YELLOW	"\e[1;33m"
#define BYELLOW	"\e[1;33m"
#define RED	"\e[31m"
#define GREEN	"\e[32m"

#define MAX_PHILO 200

// libft
int	ft_atoi(const char *str);
int	ft_isdigit(int c);

typedef	struct s_counter
{
	pthread_mutex_t	count_mutex;
	unsigned int	count;
} t_counter;

typedef	struct s_locks
{
	pthread_mutex_t	lock_1;
	pthread_mutex_t	lock_2;
	unsigned int	count;
}	t_locks;

typedef struct s_program t_program;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals_eaten;
	long			last_meal;
	int				dead;
	t_program		*data;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}					t_philo;

typedef struct s_program
{
	pthread_t		monitor;
	int				count;
	int				num_of_philos;
	int				num_times_to_eat;
	int				dead_flag;
	int				monitor_ready;
	int				all_create;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	long			start_time;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	create_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t *forks;
	t_philo			*philos;
}					t_program;

// utils_args
int	check_args(int argc, char **argv);
int	ft_isnumber(char *str);

//routine
void	*monitor(void *data);
void	*routine_philo(void *data);
void	*routine_philo_test(void *data);

// init
void	init_prog(t_program *prog, char **argv);

//utils_execution
long	get_time(void);

#endif
