/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:50:55 by yrio              #+#    #+#             */
/*   Updated: 2024/05/22 10:01:42 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_args(int argc, char **argv)
{
	int	i;

	if ((argc != 5 && argc != 6) || ft_atoi(argv[1]) > 200)
		return (0);
	i = 1;
	while (i < 5)
	{
		if(!ft_isnumber(argv[i]) || ft_atoi(argv[i]) == 0)
			return (0);
		i++;
	}
	if (argv[5] && !ft_isnumber(argv[i]))
			return (0);
	return (1);
}

int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit((int)str[i]))
			return (0);
		i++;
	}
	return (1);
}
