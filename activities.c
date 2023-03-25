/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:10:09 by zasabri           #+#    #+#             */
/*   Updated: 2023/03/25 20:35:15 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	sleeping(unsigned long time, t_infos *info)
{
	unsigned long	time2;
	unsigned long	time3;
	struct timeval	t;

	gettimeofday(&t, NULL);
	time2 = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	while (!info->if_died)
	{
		gettimeofday(&t, NULL);
		time3 = (t.tv_sec * 1000) + (t.tv_usec / 1000);
		if ((time3 - time2) >= time)
			break ;
		usleep(50);
	}
}

void	eating(t_philo *philo)
{
	t_infos			*info;
	struct timeval	t;

	gettimeofday(&t, NULL);
	info = philo->info;
	pthread_mutex_lock(&(info->fork[philo->left]));
	action_generator(info, philo->pos, "has taken a fork");
	pthread_mutex_lock(&(info->fork[philo->right]));
	action_generator(info, philo->pos, "has taken a fork");
	pthread_mutex_lock(&info->meal);
	action_generator(info, philo->pos, "is eating");
	philo->last_meal = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	pthread_mutex_unlock(&info->meal);
	sleeping(info->to_eat, info);
	philo->last_meal++;
	pthread_mutex_unlock(&(info->fork[philo->left]));
	pthread_mutex_unlock(&(info->fork[philo->right]));
}
