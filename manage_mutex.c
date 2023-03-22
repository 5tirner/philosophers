/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:10:15 by zasabri           #+#    #+#             */
/*   Updated: 2023/03/22 14:53:27 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	manage_mutex(t_infos *info)
{
	int	i;

	i = info->philo_nbr;
	while (i >= 1)
	{
		if (pthread_mutex_init(&info->fork[i], NULL))
			return (1);
		i--;
	}
	if (pthread_mutex_init(&info->meal, NULL))
		return (1);
	if (pthread_mutex_init(&info->out, NULL))
		return (1);
	return (0);
}