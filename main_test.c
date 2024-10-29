/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:02:07 by yrio              #+#    #+#             */
/*   Updated: 2024/04/02 10:06:18 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#define TIMES_TO_COUNT 21000

void	*thread_routine1(void *data)
{
	pthread_t tid;
	
	(void)data;
	tid = pthread_self();
	printf("%sThread [%ld]: Le plus grand ennui c'est d'exister sans vivre.%s\n", YELLOW, tid, NC);
	return (NULL);
}

void	*thread_routine2(void *data)
{
	pthread_t		tid;
	t_counter		*counter;
	unsigned int	i;

	tid = pthread_self();
	counter = (t_counter *)data;
	pthread_mutex_lock(&counter->count_mutex);
	printf("%sThread [%ld]: compte au depart = %u.%s\n",
		YELLOW, tid, counter->count, NC);
	pthread_mutex_unlock(&counter->count_mutex);
	i = 0;
	while (i < TIMES_TO_COUNT)
	{
		pthread_mutex_lock(&counter->count_mutex);
		counter->count++;
		pthread_mutex_unlock(&counter->count_mutex);
		i++;
	}
	pthread_mutex_lock(&counter->count_mutex);
	printf("%sThread [%ld]: Compte final = %u.%s\n",
		BYELLOW, tid, counter->count, NC);
	pthread_mutex_unlock(&counter->count_mutex);
	return (NULL);
}

void	*thread_3_routine(void *data)
{
	pthread_t	tid;
	t_locks		*locks;
	
	tid = pthread_self();
	locks = (t_locks *)data;
	printf("%sThread [%ld]: veut verrouiller lock 1%s\n", YELLOW, tid, NC);
	pthread_mutex_lock(&locks->lock_1);
	printf("%sThread [%ld]: possede lock 1%s\n", BYELLOW, tid, NC);
	printf("%sThread [%ld]: veut verrouiller lock 2%s\n", YELLOW, tid, NC);
	pthread_mutex_lock(&locks->lock_2);
	printf("%sThread [%ld]: possede lock 2%s\n", BYELLOW, tid, NC);
	locks->count += 1;
	printf("%sThread [%ld]: deverouille lock 2%s\n", BYELLOW, tid, NC);
	pthread_mutex_unlock(&locks->lock_2);
	printf("%sThread [%ld]: deverouille lock 1%s\n", BYELLOW, tid, NC);
	pthread_mutex_unlock(&locks->lock_1);
	printf("%sThread [%ld]: termine%s\n", YELLOW, tid, NC);
	return (NULL); // Le thread termine ici.
}

void	*thread_4_routine(void *data)
{
	pthread_t	tid;
	t_locks		*locks;
	
	tid = pthread_self();
	locks = (t_locks *)data;
	printf("%sThread [%ld]: veut verrouiller lock 2%s\n", YELLOW, tid, NC);
	pthread_mutex_lock(&locks->lock_2);
	printf("%sThread [%ld]: possede lock 2%s\n", BYELLOW, tid, NC);
	printf("%sThread [%ld]: veut verrouiller lock 1%s\n", YELLOW, tid, NC);
	pthread_mutex_lock(&locks->lock_1);
	printf("%sThread [%ld]: possede lock 1%s\n", BYELLOW, tid, NC);
	locks->count += 1;
	printf("%sThread [%ld]: deverouille lock 1%s\n", BYELLOW, tid, NC);
	pthread_mutex_unlock(&locks->lock_1);
	printf("%sThread [%ld]: deverouille lock 2%s\n", BYELLOW, tid, NC);
	pthread_mutex_unlock(&locks->lock_2);
	printf("%sThread [%ld]: termine%s\n", YELLOW, tid, NC);
	return (NULL); // Le thread termine ici.
}

int	main(void)
{
	pthread_t	tid1;	// Identifiant du premier thread
	pthread_t	tid2;	// Identifiant du second thread
	t_locks		locks;	// Structure contenant 2 mutex

	locks.count = 0;
	// Initialisation des deux mutex :
	pthread_mutex_init(&locks.lock_1, NULL);
	pthread_mutex_init(&locks.lock_2, NULL);
	// Création des threads :
	pthread_create(&tid1, NULL, thread_3_routine, &locks);
	printf("Main: Creation du premier thread [%ld]\n", tid1);
	pthread_create(&tid2, NULL, thread_4_routine, &locks);
	printf("Main: Creation du second thread [%ld]\n", tid2);
	// Union des threads :
	pthread_join(tid1, NULL);
	printf("Main: Union du premier thread [%ld]\n", tid1);
	pthread_join(tid2, NULL);
	printf("Main: Union du second thread [%ld]\n", tid2);
	// Évaluation du résultat :
	if (locks.count == 2)
		printf("%sMain: OK: Le compte est %d\n", GREEN, locks.count);
	else
		printf("%sMain: ERREUR: Le compte est%u\n", RED, locks.count);
	// Destruction des mutex :
	pthread_mutex_destroy(&locks.lock_1);
	pthread_mutex_destroy(&locks.lock_2);
	return (0);
}

// int	main(void)
// {
// 	pthread_t		tid1;
// 	pthread_t		tid2;
// 	t_counter		counter;

// 	counter.count = 0;
// 	pthread_mutex_init(&counter.count_mutex, NULL);
// 	printf("Main: Le compte attendu est de %s%u%s\n", GREEN, 
// 					2 * TIMES_TO_COUNT, NC);
// 	pthread_create(&tid1, NULL, thread_routine2, &counter);
// 	printf("Main: Creation du premier thread [%ld]\n", tid1);
// 	pthread_create(&tid2, NULL, thread_routine2, &counter);
// 	printf("Main: Creation du second thread [%ld]\n", tid2);
// 	pthread_join(tid1, NULL);
// 	printf("Main: Union du premier thread [%ld]\n", tid1);
// 	pthread_join(tid2, NULL);
// 	printf("Main: Union du second thread [%ld]\n", tid2);
// 	if (counter.count != (2 * TIMES_TO_COUNT))
// 		printf("%sMain: ERREUR ! Le compte est de %u%s\n", RED, counter.count, NC);
// 	else
// 		printf("%sMain: OK. Le compte est de %u%s\n", GREEN, counter.count, NC);
// 	pthread_mutex_destroy(&counter.count_mutex);
// 	return (0);
// }
