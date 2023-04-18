/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:21:20 by zasabri           #+#    #+#             */
/*   Updated: 2023/04/18 23:16:36 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	take_forks(t_infos *info, pthread_mutex_t *r, pthread_mutex_t *l, int p)
{
	pthread_mutex_lock(&info->write);
	printf("%ldms philo %d has taken a fork\n",
		time_generate() - info->t_zero, p + 1);
	pthread_mutex_unlock(&info->write);
	pthread_mutex_lock(r);
	pthread_mutex_lock(&info->write);
	printf("%ldms philo %d has taken a fork\n",
		time_generate() - info->t_zero, p + 1);
	pthread_mutex_unlock(&info->write);
	pthread_mutex_lock(l);
}
