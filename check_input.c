/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 17:32:05 by zasabri           #+#    #+#             */
/*   Updated: 2023/04/16 17:38:46 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_this_arg(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if ((av[i] != '+')
			&& (av[i] < '0' || av[i] > '9'))
			return (1);
		if (i != 0 && (av[i] < '0' || av[i] > '9'))
			return (1);
		i++;
	}
	return (0);
}

int	check_input(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (check_this_arg(av[i]))
			return (printf("Problem here: %s\n", av[i]));
		i++;
	}	
	return (0);
}

int	initialize_input(char **argv, int argc, t_infos *info)
{
	info->philo_nbr = ft_atoi(argv[1]);
	if (info->philo_nbr <= 0 || info->philo_nbr > 200)
		return (printf("0 < philo_nbr < 200\n"));
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->time_to_die = ft_atoi(argv[2]);
	if (info->time_to_die < 60 || info->time_to_eat < 60
		|| info->time_to_die < 60)
		return (printf("the times should be 60ms or more\n"));
	info->meals_nbr = 0;
	if (argc == 6)
	{
		info->meals = ft_atoi(argv[5]);
		if (info->meals == 0)
			return (printf("meals_nbr shoul be 1 or more\n"));
	}
	else
		info->meals = -1;
	return (0);
}
