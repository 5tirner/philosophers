/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:20:55 by zasabri           #+#    #+#             */
/*   Updated: 2023/04/17 22:55:49 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	take_break(int ts)
{
	time_t	t0;

	t0 = time_generate();
	while (time_generate() - t0 < ts)
		usleep(500);
}

void	activities(t_infos *info, pthread_mutex_t *r, pthread_mutex_t *l, int p)
{
	pthread_mutex_lock(&info->increment);
	info->meals_nbr++;
	pthread_mutex_unlock(&info->increment);
	take_break(info->time_to_eat);
	pthread_mutex_unlock(l);
	pthread_mutex_unlock(r);
	pthread_mutex_lock(&info->write);
	printf("%ld: philo %d is sleeping\n", time_generate(), p + 1);
	pthread_mutex_unlock(&info->write);
	take_break(info->time_to_sleep);
	pthread_mutex_lock(&info->write);
	printf("%ld: philo %d is thinking\n", time_generate(), p + 1);
	pthread_mutex_unlock(&info->write);
}

void	*philosopher(void *arg)
{
	t_infos			*info;
	pthread_mutex_t	*right;
	pthread_mutex_t	*left;
	int				pos;

	info = (t_infos *)arg;
	pos = info->id;
	right = info->fork + pos;
	left = info->fork + ((pos + 1) % info->philo_nbr);
	while (1)
	{
		pthread_mutex_lock(left);
		pthread_mutex_lock(&info->write);
		printf("%ld: philo %d has taken a fork\n", time_generate(), pos + 1);
		pthread_mutex_unlock(&info->write);
		pthread_mutex_lock(right);
		pthread_mutex_lock(&info->write);
		printf("%ld: philo %d has taken a fork\n", time_generate(), pos + 1);
		pthread_mutex_unlock(&info->write);
		info->lastmeal[pos] = time_generate();
		pthread_mutex_lock(&info->write);
		printf("%ld: philo %d is eating\n", time_generate(), pos + 1);
		pthread_mutex_unlock(&info->write);
		activities(info, right, left, pos);
	}
}

int	initialize_mutex(t_infos *info)
{
	int	i;

	i = 0;
	info->fork = malloc(sizeof(pthread_mutex_t) * info->philo_nbr);
	info->lastmeal = malloc(sizeof(time_t) * info->philo_nbr);
	pthread_mutex_init(&info->write, NULL);
	pthread_mutex_init(&info->increment, NULL);
	while (i < info->philo_nbr)
	{
		if (pthread_mutex_init(&(info->fork[i]), NULL))
			return (printf("Error in mutex_init\n"));
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	pthread_t	*philo;
	t_infos		info;
	int			i;

	if (ac == 5 || ac == 6)
	{
		i = -1;
		if (check_input(av))
			return (1);
		if (initialize_input(av, ac, &info))
			return (1);
		if (initialize_mutex(&info))
			return (1);
		philo = malloc(sizeof(pthread_t) * info.philo_nbr);
		while (++i < info.philo_nbr)
		{
			info.id = i;
			info.lastmeal[i] = time_generate();
			if (pthread_create(&philo[i], NULL, &philosopher, &info))
				return (printf("Error in pthread_create\n"));
			usleep(500);
		}
		return (stop(&info));
	}
	return (printf("Ilegal numbre of argements\n"));
}
