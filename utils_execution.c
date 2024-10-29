/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:42:04 by yrio              #+#    #+#             */
/*   Updated: 2024/05/22 09:54:06 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time(void)
{
	struct timeval tv;
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
