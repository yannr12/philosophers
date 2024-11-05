/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:42:04 by yrio              #+#    #+#             */
/*   Updated: 2024/11/05 17:26:47 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time(void)
{
	struct timeval	tv;
	time_t			secondes;
	suseconds_t		microsecondes;
	long			time;

	if (gettimeofday(&tv, NULL) == -1)
		return (printf("gettimeofday failed\n"), -1);
	secondes = tv.tv_sec;
	microsecondes = tv.tv_usec;
	time = 1000 * secondes + microsecondes / 1000;
	return (time);
}

void	print_message(char *str, t_philo *philo)
{
	size_t	time;

	if (dead_loop(philo))
		return ;
	pthread_mutex_lock(&philo->data->write_lock);
	time = get_time() - philo->data->start_time;
	printf("%zu %i %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->write_lock);
}

void	print_died(char *str, t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->data->write_lock);
	time = get_time() - philo->data->start_time;
	printf("%zu %i %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->write_lock);
}

void	ft_usleep(int time_sleep)
{
	long	start_time;

	start_time = get_time();
	while (get_time() - start_time < time_sleep)
		usleep(500);
}

int	dead_loop(t_philo *philo)
{
	int	count;

	count = 0;
	pthread_mutex_lock(&philo->data->dead_lock);
	while (count < philo->data->num_of_philos)
	{
		if (philo->data->philos[count].dead)
		{
			pthread_mutex_unlock(&philo->data->dead_lock);
			return (1);
		}
		count++;
	}
	if (philo->data->finish)
	{
		pthread_mutex_unlock(&philo->data->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead_lock);
	return (0);
}
