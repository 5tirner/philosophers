/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_finish.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 23:15:28 by zasabri           #+#    #+#             */
/*   Updated: 2023/04/16 23:29:38 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	stop(t_infos *info)
{
	time_t	t;
	int		i;

	while (1)
	{
		i = 0;
		t = time_generate();
		while (i < info->philo_nbr)
		{
			if (info->meals != -1
				&& info->meals_nbr >= (info->meals * info->philo_nbr))
				return (0);
			if (t - info->lastmeal[i] > info->time_to_die)
			{		
				pthread_mutex_lock(&info->write);
				printf("%ld: philo %d is died\n", time_generate(), i + 1);
				pthread_mutex_unlock(&info->write);
				return (1);
			}
			i++;
		}
	}
}
