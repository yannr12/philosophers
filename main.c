/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:21:49 by yrio              #+#    #+#             */
/*   Updated: 2024/10/15 15:12:26 by yrio             ###   ########.fr       */
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

void *thread_routine()
{
	pthread_t tid;

	tid = pthread_self();
	printf("%sThread [%ld]: Salut%s\n",
	YELLOW, tid, NC);
	return (NULL); // Le thread termine ici.
}

int launch_philo(t_program *prog)
{
	pthread_t tid[prog->num_of_philos];
	int		  num_philos;
	int		  count;
	
	num_philos = prog->num_of_philos;
	count = 0;
	while (count < num_philos)
	{
		pthread_create(&tid[count], NULL, thread_routine, NULL);
		printf("Main: Creation du thread [%ld]\n", tid[count]);
		count++;
	}
	count = 0;
	while (count < num_philos)
	{
		pthread_join(tid[count], NULL);
		printf("Main: Union du premier thread [%ld]\n", tid[count]);
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
