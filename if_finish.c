/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_finish.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 23:15:28 by zasabri           #+#    #+#             */
/*   Updated: 2023/04/17 20:14:27 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	destroy_mutexes(t_infos *info)
{
	int	i;

	i = 0;
	while (i < info->philo_nbr)
	{
		pthread_mutex_destroy(&info->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&info->write);
	pthread_mutex_destroy(&info->increment);
}

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
			{
				destroy_mutexes(info);
				return (0);
			}
			if (t - info->lastmeal[i] > info->time_to_die)
			{		
				pthread_mutex_lock(&info->write);
				printf("%ld: philo %d is died\n", time_generate(), i + 1);
				pthread_mutex_unlock(&info->write);
				destroy_mutexes(info);
				return (0);
			}
			i++;
		}
	}
}
