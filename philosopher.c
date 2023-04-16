/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:20:55 by zasabri           #+#    #+#             */
/*   Updated: 2023/04/16 03:26:36 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_this_arg(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if ((av[i] != '+')
			&& (av[i] < '0' || av[i] > '9'))
			return (1);
		if (i != 0 && (av[i] < '0' || av[i] > '9'))
			return (1);
		i++;
	}
	return (0);
}

int	check_input(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (check_this_arg(av[i]))
			return (printf("Problem here: %s\n", av[i]));
		i++;
	}	
	return (0);
}

time_t	time_generate(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	sleping(int ts)
{
	time_t	t0;

	t0 = time_generate();
	while (time_generate() - t0 < ts)
		usleep(500);
}

void	activities(t_infos	*info, pthread_mutex_t	*right,
			pthread_mutex_t	*left, int pos)
{
	info->meals_nbr++;
	sleping(info->time_to_eat);
	pthread_mutex_unlock(right);
	pthread_mutex_unlock(left);
	pthread_mutex_lock(info->write);
	printf("%ld: philo %d is sleeping\n", time_generate(), pos + 1);
	pthread_mutex_unlock(info->write);
	sleping(info->time_to_sleep);
	pthread_mutex_lock(info->write);
	printf("%ld: philo %d is thinking\n", time_generate(), pos + 1);
	pthread_mutex_unlock(info->write);
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
		pthread_mutex_lock(info->write);
		printf("%ld: philo %d has taken a fork\n", time_generate(), pos + 1);
		pthread_mutex_unlock(info->write);
		pthread_mutex_lock(right);
		pthread_mutex_lock(info->write);
		printf("%ld: philo %d has taken a fork\n", time_generate(), pos + 1);
		pthread_mutex_unlock(info->write);
		info->lastmeal[pos] = time_generate();
		pthread_mutex_lock(info->write);
		printf("%ld: philo %d is eating\n", time_generate(), pos + 1);
		pthread_mutex_unlock(info->write);
		pthread_mutex_unlock(left);
		pthread_mutex_unlock(right);
		activities(info, right, left, pos);
	}
	return (NULL);
}

int	initialize_input(char **argv, int argc, t_infos *info)
{
	info->philo_nbr = ft_atoi(argv[1]);
	if (info->philo_nbr <= 0 || info->philo_nbr > 200)
		return (printf("0 < philo_nbr < 200\n"));
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->time_to_die = ft_atoi(argv[2]);
	if (info->time_to_die < 60 || info->time_to_eat < 60
		|| info->time_to_die < 60)
		return (printf("the times should be 60ms or more\n"));
	info->meals_nbr = 0;
	if (argc == 6)
	{
		info->meals = ft_atoi(argv[5]);
		if (info->meals == 0)
			return (printf("meals_nbr shoul be 1 or more\n"));
	}
	else
		info->meals = -1;

	return (0);
}

int	initialize_mutex(t_infos *info)
{
	int	i;

	i = 0;
	info->fork = malloc(sizeof(pthread_mutex_t) * info->philo_nbr);
	info->lastmeal = malloc(sizeof(time_t) * info->philo_nbr);
	info->write = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(info->write, NULL);
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
				pthread_mutex_lock(info->write);
				printf("%ld: philo %d is died\n", time_generate(), i + 1);
				pthread_mutex_unlock(info->write);
				return (1);
			}
			i++;
		}
	}
}

int	main(int ac, char **av)
{
	pthread_t	*philo;
	t_infos		info;
	int			i;

	if (ac == 5 || ac == 6)
	{
		i = 0;
		if (check_input(av))
			return (1);
		if (initialize_input(av, ac, &info))
			return (1);
		if (initialize_mutex(&info))
			return (1);
		philo = malloc(sizeof(pthread_t) * info.philo_nbr);
		while (i < info.philo_nbr)
		{
			info.id = i;
			info.lastmeal[i] = time_generate();
			if (pthread_create(&philo[i], NULL, &philosopher, &info))
				return (printf("Error in pthread_creat\n"));
			usleep(500);
			i++;
		}
		return (stop(&info));
	}
	else
		return (printf("Ilegal numbre of argements\n"));
}
