/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_finish.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 23:15:28 by zasabri           #+#    #+#             */
/*   Updated: 2023/04/20 04:19:23 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	stop(t_infos *p)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < p->philo_nbr)
		{
			if (p->all_eat && p->meals_nbr > p->all_eat)
				return (0);
			pthread_mutex_lock(&p->increment);
			if (time_generate() - p->lastmeal[i] > p->time_to_die)
			{	
				pthread_mutex_lock(&p->write);
				printf("%ldms philo %d is died\n",
					time_generate() - p->t_zero, i + 1);
				return (1);
			}
			pthread_mutex_unlock(&p->increment);
		}
	}
}
