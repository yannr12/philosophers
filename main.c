/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:21:49 by yrio              #+#    #+#             */
/*   Updated: 2024/11/04 17:30:33 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	wait_threads(t_program *prog)
{
	int	i;

	i = 0;
	while (i < prog->num_of_philos)
	{
		pthread_join(prog->philos[i].thread, NULL);
		i++;
	}
	return (1);
}

void *thread_routine(void *data)
{
	t_philo		*philo;

	philo = (t_philo *)data;
	if (philo->id % 2)
	{
		ft_usleep(5);
		think_routine(philo);
	}
	while (!dead_loop(philo))
	{
		eat_routine(philo);
		sleep_routine(philo);
		think_routine(philo);
	}
	return (NULL);
}

int launch_philo(t_program *prog)
{
	pthread_t	observer;
	pthread_t	tid[prog->num_of_philos];
	int		  	num_philos;
	int		  	count;
	
	prog->start_time = get_time();
	num_philos = prog->num_of_philos;
	count = 0;
	pthread_create(&observer, NULL, monitor, prog);
	while (count < num_philos)
	{
		pthread_create(&tid[count], NULL, thread_routine, &prog->philos[count]);
		count++;
	}
	count = 0;
	while (count < num_philos)
	{
		pthread_join(tid[count], NULL);
		count++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_program	prog;

	if (!check_args(argc, argv))
	{
		printf("False\n");
		return (0);
	}
	init_prog(&prog, argv);
	launch_philo(&prog);
	printf("Simulation ended\n");
	return (1);
}
