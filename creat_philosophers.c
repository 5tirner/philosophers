/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_philosophers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:00:59 by zasabri           #+#    #+#             */
/*   Updated: 2023/03/27 21:40:16 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	create_philosophers(t_infos *info)
{
	int	i;
	int	ph_nb;

	i = info->philo_nbr;
	ph_nb = info->philo_nbr;
	while (i >= 1)
	{
		info->philo[i].pos = i;
		info->philo[i].eat = 0;
		info->philo[i].left = i;
		if (i + 1 == ph_nb)
			info->philo[i].right = ph_nb;
		else
			info->philo[i].right = (i + 1) % ph_nb;
		info->philo[i].last_meal = 0;
		i--;
	}
}

int	start_working(t_infos *info)
{
	int				i;
	t_philo			*philo;
	struct timeval	t;
	pthread_t		t1;

	i = 0;
	philo = info->philo;
	gettimeofday(&t, NULL);
	info->timer = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	while (i < info->philo_nbr)
	{
		gettimeofday(&t, NULL);
		if (pthread_create(&philo[i].pos, NULL, &t1, &(philo[i])))
			return (1);
		philo[i].last_meal = (t.tv_sec * 1000) + (t.tv_usec / 1000);
		i++;
	}
	return (0);
}
