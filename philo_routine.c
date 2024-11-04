/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:58:21 by yrio              #+#    #+#             */
/*   Updated: 2024/11/04 17:46:50 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	think_routine(t_philo *philo)
{
	print_message("is thinking", philo);
	return (1);
}

int	eat_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_message("has taken a fork", philo);
	if (philo->data->num_of_philos == 1)
	{
		ft_usleep(philo->data->time_to_die);
		pthread_mutex_unlock(philo->r_fork);
		return (0);
	}
	pthread_mutex_lock(philo->l_fork);
	print_message("has taken a fork", philo);
	philo->is_eating = 1;
	print_message("is eating", philo);
	philo->last_meal = get_time();
	philo->meals_eaten = philo->meals_eaten + 1;
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	philo->is_eating = 0;
	return (1);
}

int	sleep_routine(t_philo *philo)
{
	print_message("is sleeping", philo);
	ft_usleep(philo->data->time_to_sleep);
	return (1);
}
