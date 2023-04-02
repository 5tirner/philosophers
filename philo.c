/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 18:32:01 by zasabri           #+#    #+#             */
/*   Updated: 2023/04/01 00:31:53 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_issues(t_infos *info)
{
	int	i;

	i = info->ph_nb - 1;
	while (i >= 0)
	{
		info->philo[i].right = i;
		info->philo[i].left = (i + 1) % info->ph_nb;
		info->philo[i].last_meal = 0;
		info->philo[i].pos = i;
		i--;
	}
	i = 0;
	while (i < info->ph_nb)
	{
		printf("Right: %d | Left: %d\n", info->philo[i].right, info->philo[i].left);
		i++;
	}	
}

int	start_initialize(t_infos *info, char **av, int ac)
{
	info->ph_nb = ft_atoi(av[1]);
	if (info->ph_nb > 200 || info->ph_nb <= 0)
		return (printf("1 <= PHILO_NUMBERS <= 200\n"));
	info->die = ft_atoi(av[2]);
	info->eat = ft_atoi(av[3]);
	info->sleep = ft_atoi(av[4]);
	if (info->die < 60 || info->eat < 60 || info->sleep < 60)
		return (printf("Enter Times more or equal 60ms\n"));
	if (ac == 5)
		info->m_nbr = -1;
	else
	{
		info->m_nbr = ft_atoi(av[5]);
		if (info->m_nbr <= 0)
			return (1);
	}
	return (0);
}

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
			return (printf("Problem Here: %s\n", av[i]));
		i++;
	}	
	return (0);
}

int main(int ac, char **av)
{
	t_infos		info;

	if (ac == 5 || ac == 6)
	{
		if (check_input(av))
			return (1);
		if (start_initialize(&info, av, ac))
			return (1);
		info.philo = malloc(sizeof(t_philos) * info.ph_nb);
		philo_issues(&info);
		//info.forks = malloc(sizeof(t_philos) * info.ph_nb);
	}
	else
		write(2, "Ivalid Number of Argements\n", 28);
}