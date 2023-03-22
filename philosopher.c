/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:20:55 by zasabri           #+#    #+#             */
/*   Updated: 2023/03/22 09:56:52 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	init_times(int ac, char **av, t_infos *infos)
{
	infos->philo_nbr = ft_atoi(av[1]);
	infos->to_die = ft_atoi(av[2]);
	infos->to_eat = ft_atoi(av[3]);
	infos->to_sleep = ft_atoi(av[4]);
	if (ac == 5)
		infos->repeat_eat = -1;
	if (ac == 6)
		infos->repeat_eat = ft_atoi(av[5]);
}

int	check_that_arg(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if ((av[i] < '0' || av[i] > '9') && (av[i] != '+'))
			return (1);
		if (i != 0 && av[i] == '+')
			return (1);
		i++;
	}
	return (0);
}

int	check_input(t_infos *info, char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (check_that_arg(av[i]))
		{
			write(2, "Problem Here: ", 14);
			write(2, av[i], ft_strlen(av[i]));
			write(2, "\n", 1);
			return (1);
		}
		i++;
	}
	if (info->philo_nbr == 0 || info->to_die == 0
		|| info->to_eat == 0 || info->to_sleep == 0)
	{
		write(2, "Zero? We don't Do This Here!\n", 29);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_infos	infos;

	if (ac == 5 || ac == 6)
	{
		init_times(ac, av, &infos);
		if (check_input(&infos, av))
			return (1);
	}
	else
	{
		write(2, "Invalid Number Of Argements\n", 28);
		return (1);
	}
}
