/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_finish.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 23:15:28 by zasabri           #+#    #+#             */
/*   Updated: 2023/04/18 22:50:32 by zasabri          ###   ########.fr       */
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

int	stop(t_infos *p)
{
	time_t	t;
	int		i;

	while (1)
	{
		i = 0;
		t = time_generate() - p->t_zero;
		while (i < p->philo_nbr)
		{
			if (p->meals != -1 && p->meals_nbr >= (p->meals * p->philo_nbr))
			{
				destroy_mutexes(p);
				return (0);
			}
			if (t - p->lastmeal[i] > p->time_to_die)
			{		
				pthread_mutex_lock(&p->write);
				printf("%ldms philo %d is died\n", time_generate(), i + 1);
				pthread_mutex_unlock(&p->write);
				destroy_mutexes(p);
				return (1);
			}
			i++;
		}
	}
}
