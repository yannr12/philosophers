/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:58:21 by yrio              #+#    #+#             */
/*   Updated: 2024/11/08 12:34:21 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	think_routine(t_philo *philo)
{
	ft_usleep(5);
	print_message("is thinking", philo);
	return (1);
}

int	lock_forks(t_philo *philo)
{
	if (philo->id % 2)
		pthread_mutex_lock(philo->r_fork);
	else
		pthread_mutex_lock(philo->l_fork);
	print_message("has taken a fork", philo);
	if (philo->data->num_of_philos == 1)
	{
		ft_usleep(philo->data->time_to_die);
		if (philo->id % 2)
			pthread_mutex_unlock(philo->r_fork);
		else
			pthread_mutex_unlock(philo->l_fork);
		return (0);
	}
	if (philo->id % 2)
		pthread_mutex_lock(philo->l_fork);
	else
		pthread_mutex_lock(philo->r_fork);
	print_message("has taken a fork", philo);
	return (1);
}

void	unlock_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
}

int	eat_routine(t_philo *philo)
{
	if (lock_forks(philo) == 0)
		return (0);
	print_message("is eating", philo);
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_meal = get_time();
	philo->is_eating = 1;
	pthread_mutex_unlock(&philo->data->meal_lock);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->meals_eaten = philo->meals_eaten + 1;
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->data->meal_lock);
	unlock_forks(philo);
	return (1);
}

int	sleep_routine(t_philo *philo)
{
	print_message("is sleeping", philo);
	ft_usleep(philo->data->time_to_sleep);
	return (1);
}
