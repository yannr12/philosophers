/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:40:41 by yrio              #+#    #+#             */
/*   Updated: 2024/11/05 17:20:32 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_death(t_program *prog)
{
	int		count;

	count = 0;
	pthread_mutex_lock(&prog->meal_lock);
	while (count < prog->num_of_philos)
	{
		if (get_time() - prog->philos[count].last_meal
			>= (long)prog->time_to_die && prog->philos[count].is_eating == 0)
		{
			pthread_mutex_lock(&prog->dead_lock);
			prog->philos[count].dead = 1;
			pthread_mutex_unlock(&prog->dead_lock);
			print_died("died", &prog->philos[count]);
			pthread_mutex_unlock(&prog->meal_lock);
			return (1);
		}
		count++;
	}
	pthread_mutex_unlock(&prog->meal_lock);
	return (0);
}

int	check_end(t_program *prog)
{
	int	count;

	count = 0;
	if (prog->num_times_to_eat != -1)
	{
		pthread_mutex_lock(&prog->meal_lock);
		while (count < prog->num_of_philos)
		{
			if (prog->num_times_to_eat != prog->philos[count].meals_eaten)
			{
				pthread_mutex_unlock(&prog->meal_lock);
				return (0);
			}
			count++;
		}
		pthread_mutex_unlock(&prog->meal_lock);
		pthread_mutex_lock(&prog->dead_lock);
		prog->finish = 1;
		pthread_mutex_unlock(&prog->dead_lock);
		return (1);
	}
	return (0);
}

void	*monitor(void *data)
{
	t_program	*prog;

	prog = (t_program *)data;
	while (1)
	{
		if (check_death(prog) || check_end(prog))
			break ;
		ft_usleep(5);
	}
	return (NULL);
}
