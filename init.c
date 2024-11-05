/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:21:59 by yrio              #+#    #+#             */
/*   Updated: 2024/11/05 12:25:38 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_forks(pthread_mutex_t *forks, char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_philo(t_program *prog, char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		prog->philos[i].data = prog;
		prog->philos[i].id = i + 1;
		prog->philos[i].meals_eaten = 0;
		prog->philos[i].last_meal = get_time();
		prog->philos[i].is_eating = 0;
		prog->philos[i].dead = 0;
		prog->philos[i].r_fork = &prog->forks[i];
		if (i != ft_atoi(argv[1]) - 1)
			prog->philos[i].l_fork = &prog->forks[i + 1];
		else if (i == ft_atoi(argv[1]) - 1 && ft_atoi(argv[1]) != 1)
			prog->philos[i].l_fork = &prog->forks[0];
		i++;
	}
}

void	init_prog(t_program *prog, char **argv)
{
	memset(prog, 0, sizeof(t_program));
	prog->monitor_ready = 0;
	prog->count = 0;
	prog->start_time = -1;
	prog->finish = 0;
	prog->num_of_philos = ft_atoi(argv[1]);
	prog->time_to_die = ft_atoi(argv[2]);
	prog->time_to_eat = ft_atoi(argv[3]);
	prog->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		prog->num_times_to_eat = ft_atoi(argv[5]);
	else
		prog->num_times_to_eat = -1;
	pthread_mutex_init(&prog->write_lock, NULL);
	pthread_mutex_init(&prog->create_lock, NULL);
	pthread_mutex_init(&prog->dead_lock, NULL);
	prog->forks = malloc((prog->num_of_philos + 1) * sizeof(pthread_mutex_t));
	init_forks(prog->forks, argv);
	prog->philos = malloc((prog->num_of_philos + 1) * sizeof(t_philo));
	init_philo(prog, argv);
}
