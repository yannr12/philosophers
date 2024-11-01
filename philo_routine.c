/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:58:21 by yrio              #+#    #+#             */
/*   Updated: 2024/11/01 16:22:47 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	eat_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(&philo->data->write_lock);
	printf("%li %i has taken a fork\n", get_time() - philo->data->start_time,
		philo->id);
	pthread_mutex_unlock(&philo->data->write_lock);

	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(&philo->data->write_lock);
	printf("%li %i has taken a fork\n", get_time() - philo->data->start_time, 
		philo->id);
	pthread_mutex_unlock(&philo->data->write_lock);
	
	sleep(2);
	
	pthread_mutex_lock(&philo->data->write_lock);
	printf("%li %i is eating\n", get_time() - philo->data->start_time, 
		philo->id);
	pthread_mutex_unlock(&philo->data->write_lock);
	
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (1);
}
