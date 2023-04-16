/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:20:55 by zasabri           #+#    #+#             */
/*   Updated: 2023/04/16 23:05:52 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

time_t	time_generate(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	take_break(int ts)
{
	time_t	t0;

	t0 = time_generate();
	while (time_generate() - t0 < ts)
		usleep(500);
}

int	activities(t_infos *info, pthread_mutex_t *r, pthread_mutex_t *l, int p)
{
	if (pthread_mutex_lock(&info->increment))
		return (printf("Error in mutex_lock\n"));
	info->meals_nbr++;
	if (pthread_mutex_unlock(&info->increment))
		return (printf("Error in mutex_unlock\n"));
	take_break(info->time_to_eat);
	if (pthread_mutex_unlock(l))
		return (printf("Error in mutex_unlock\n"));
	if (pthread_mutex_unlock(r))
		return (printf("Error in mutex_lock\n"));
	if (pthread_mutex_lock(&info->write))
		return (printf("Error in mutex_lock\n"));
	printf("%ld: philo %d is sleeping\n", time_generate(), p + 1);
	if (pthread_mutex_unlock(&info->write))
		return (printf("Error in mutex_unlock\n"));
	take_break(info->time_to_sleep);
	if (pthread_mutex_lock(&info->write))
		return (printf("Error in mutex_lock\n"));
	printf("%ld: philo %d is thinking\n", time_generate(), p + 1);
	if (pthread_mutex_unlock(&info->write))
		return (printf("Error in mutex_unlock\n"));
	return (0);
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
		if (activities(info, right, left, pos))
			return ("EXIT\n");
	}
	return (NULL);
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

int	destroy_mutexes(t_infos *info)
{
	int	i;

	i = 0;
	while (i < info->philo_nbr)
	{
		if (pthread_mutex_destroy(&info->fork[i]))
			return (printf("Error in mutex_destroy\n"));
		i++;
	}
	if (pthread_mutex_destroy(&info->write))
		return (printf("Error in mutex_destroy\n"));
	if (pthread_mutex_destroy(&info->increment))
		return (printf("Error in mutex_destroy\n"));
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
				return (printf("Error in pthread_creat\n"));
			usleep(500);
		}
		//i = -1;
		// while (++i < info.philo_nbr)
		// {
			// if (pthread_join(philo[i], NULL))
				// return (printf("Error in pthread_join\n"));
		// }
		// if (destroy_mutexes(&info) != 0)
			// return (1);
		return (stop(&info));
	}
	else
		return (printf("Ilegal numbre of argements\n"));
}
