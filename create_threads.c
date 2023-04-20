/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 04:56:23 by zasabri           #+#    #+#             */
/*   Updated: 2023/04/20 05:01:38 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	creat_threads(t_infos *info, pthread_t *philo)
{
	int	i;

	i = -1;
	while (++i < info->philo_nbr)
	{
		pthread_mutex_lock(&info->increment);
		info->id = i;
		info->lastmeal[i] = time_generate();
		pthread_mutex_unlock(&info->increment);
		if (pthread_create(&philo[i], NULL, &philosopher, info))
			return (printf("Error in pthread_create\n"));
		usleep(100);
	}
	return (0);
}
