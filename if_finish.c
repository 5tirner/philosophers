/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_finish.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 23:15:28 by zasabri           #+#    #+#             */
/*   Updated: 2023/04/19 22:38:30 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	stop(t_infos *p)
{
	int	i;
	
	p->checker = 0;
	while (1)
	{
		i = -1;
		while (++i < p->philo_nbr)
		{
			if (p->all_eat && p->meals_nbr > p->all_eat)
			{
				p->checker = 1;
				break;
			}
			if (time_generate() - p->lastmeal[i] > p->time_to_die)
			{		
				pthread_mutex_lock(&p->write);
				printf("%ldms philo %d is died\n",
					time_generate() - p->t_zero, i + 1);
				pthread_mutex_unlock(&p->write);
				p->checker = 1;
				break;
			}
		}
		if (p->checker == 1)
			break;
	}
}
