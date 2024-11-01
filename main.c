/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:21:49 by yrio              #+#    #+#             */
/*   Updated: 2024/11/01 16:27:57 by yrio             ###   ########.fr       */
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
	pthread_t	tid;
	t_philo		*philo;

	philo = (t_philo *)data;
	tid = pthread_self();
	pthread_mutex_lock(&philo->data->write_lock);
	philo->data->count = philo->data->count + 1;
	printf("count : %d\n", philo->data->count);
	printf("%sThread [%ld]: Salut%s\n", YELLOW, tid, NC);
	pthread_mutex_unlock(&philo->data->write_lock);
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(philo->l_fork);
	sleep(2);
	printf("%li %i is eating\n", get_time() - philo->data->start_time, 
		philo->id);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	return (NULL); // Le thread termine ici.
}

int launch_philo(t_program *prog)
{
	pthread_t tid[prog->num_of_philos];
	int		  num_philos;
	int		  count;
	
	prog->start_time = get_time();
	num_philos = prog->num_of_philos;
	count = 0;
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
