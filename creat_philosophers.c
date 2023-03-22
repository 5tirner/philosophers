/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_philosophers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:00:59 by zasabri           #+#    #+#             */
/*   Updated: 2023/03/22 12:59:18 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	creat_philosophers(t_infos *info)
{
	int	i;
	int	ph_nb;
	
	i = info->philo_nbr - 1;
	ph_nb = info->philo_nbr;
	while (i >= 0)
	{
		info->philo[i].pos = i;
		info->philo[i].eat = 0;
		info->philo[i].left = i;
		info->philo[i].right = (i + 1) % ph_nb;
		info->philo[i].last_meal = 0;
		//info->philo[i].info = info;
		i--;
	}
	// i = info->philo_nbr - 1;
	// while (i >= 0)
	// {
	// 	printf("left_hand: %d | right_hand: %d\n", info->philo[i].left, info->philo[i].right);
	// 	i--;
	// }
}