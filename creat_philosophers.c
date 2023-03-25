/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_philosophers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:00:59 by zasabri           #+#    #+#             */
/*   Updated: 2023/03/25 20:36:11 by zasabri          ###   ########.fr       */
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
