/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:20:55 by zasabri           #+#    #+#             */
/*   Updated: 2023/04/20 05:00:20 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	take_break(int ts)
{
	time_t	t0;

	t0 = time_generate();
	while (time_generate() - t0 < ts)
		usleep(100);
}

void	activities(t_infos *info, pthread_mutex_t *r, pthread_mutex_t *l, int p)
{
	take_break(info->time_to_eat);
	pthread_mutex_lock(&info->increment);
	info->meals_nbr++;
	pthread_mutex_unlock(&info->increment);
	pthread_mutex_unlock(r);
	pthread_mutex_unlock(l);
	pthread_mutex_lock(&info->write);
	printf("%ldms philo %d is sleeping\n",
		time_generate() - info->t_zero, p + 1);
	pthread_mutex_unlock(&info->write);
	take_break(info->time_to_sleep);
	pthread_mutex_lock(&info->write);
	printf("%ldms philo %d is thinking\n",
		time_generate() - info->t_zero, p + 1);
	pthread_mutex_unlock(&info->write);
}

void	*philosopher(void *arg)
{
	t_infos			*info;
	pthread_mutex_t	*right;
	pthread_mutex_t	*left;
	int				pos;

	info = (t_infos *)arg;
	pthread_mutex_lock(&info->increment);
	pos = info->id;
	pthread_mutex_unlock(&info->increment);
	right = info->fork + pos;
	left = info->fork + ((pos + 1) % info->philo_nbr);
	while (1)
	{
		take_forks(info, right, left, pos);
		pthread_mutex_lock(&info->write);
		printf("%ldms philo %d is eating\n",
			time_generate() - info->t_zero, pos + 1);
		pthread_mutex_unlock(&info->write);
		pthread_mutex_lock(&info->increment);
		info->lastmeal[pos] = time_generate();
		pthread_mutex_unlock(&info->increment);
		activities(info, right, left, pos);
	}
}

int	initialize_mutex(t_infos *info)
{
	int	i;

	i = 0;
	info->t_zero = time_generate();
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
	if (info->meals != -1)
		info->all_eat = info->meals * info->philo_nbr;
	else
		info->all_eat = 0;
	info->t_zero = time_generate();
	return (0);
}

int	main(int ac, char **av)
{
	pthread_t	*philo;
	t_infos		*info;
	int			i;

	if (ac != 5 && ac != 6)
		return (printf("Ilegal number of Args\n"));
	i = -1;
	if (check_input(av))
		return (1);
	info = malloc(sizeof(t_infos));
	if (initialize_input(av, ac, info))
		return (1);
	if (initialize_mutex(info))
		return (1);
	philo = malloc(sizeof(pthread_t) * info->philo_nbr);
	if (creat_threads(info, philo))
		return (1);
	return (stop(info));
}
