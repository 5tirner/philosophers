/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:20:55 by zasabri           #+#    #+#             */
/*   Updated: 2023/04/13 15:26:19 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_initialize(t_infos *info, char **av, int ac)
{
	info->ph_nb = ft_atoi(av[1]);
	if (info->ph_nb > 200 || info->ph_nb <= 0)
		return (printf("1 <= philo_nbr <= 200\n"));
	info->die = ft_atoi(av[2]);
	info->eat = ft_atoi(av[3]);
	info->sleep = ft_atoi(av[4]);
	if (info->die < 60 || info->eat < 60 || info->sleep < 60)
		return (printf("Enter times more or equal 60ms\n"));
	if (ac == 5)
		info->m_nbr = -1;
	else
	{
		info->m_nbr = ft_atoi(av[5]);
		if (info->m_nbr <= 0)
			return (printf("Enter meal nbr more than 0\n"));
	} 
	return (0);
}

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

void *philosopher(void *args)
{
	t_infos	*info;
	int		left;
	int		right;

	info = (t_infos *)args;
	right = info->pos;
	left = (info->pos + 1) % info->ph_nb;
	while (1)
	{
		pthread_mutex_lock(&info->write);
		printf("Philosopher %d is taken a fork\n", info->pos);  
		pthread_mutex_unlock(&info->write);
		pthread_mutex_lock(&info->forks[right]);
		pthread_mutex_lock(&info->forks[left]); 
		pthread_mutex_lock(&info->write); 
		printf("Philosopher %d is eating\n", info->pos);
		pthread_mutex_unlock(&info->write);
		sleep(info->eat);
		pthread_mutex_unlock(&info->forks[left]);
		pthread_mutex_unlock(&info->forks[right]);
		pthread_mutex_lock(&info->write);
		printf("Philosopher %d is sleeping\n", info->pos);
		pthread_mutex_unlock(&info->write);
		sleep(info->sleep);
	}
} 

int main(int ac, char **av)
{
	int i;
	t_infos		info;
	pthread_t	*t;
	
	if (ac == 5 || ac == 6)
	{
		if (check_input(av))
			return (1);
		if (start_initialize(&info, av, ac))
			return (1);
		info.forks = malloc(sizeof(pthread_mutex_t) * info.ph_nb);
		i = -1;
		if (pthread_mutex_init(&info.write, NULL))
			return (printf("Somthing wrong happen\n"));
		while (++i < info.ph_nb)
		{
			if (pthread_mutex_init(&info.forks[i], NULL))
				return (printf("Somthin wrong happen\n"));
		}
		t = malloc(sizeof(pthread_t) * info.ph_nb);
		i = -1;
		while (++i < info.ph_nb)
		{
			info.pos = i + 1;
			usleep(50);
			if (pthread_create(&t[i], NULL, philosopher, &info))
				return (printf("Thread creat failed\n"));
		}
		i = -1;
		while (++i < info.ph_nb)
		{
			if (pthread_join(t[i], NULL))
				return (printf("Somthing wrong happen\n"));
		}
		i = -1;
		while (++i < info.ph_nb)
		{
			if (pthread_mutex_destroy(&info.forks[i]))
				return (printf("Somthing wrong happen\n"));
		}
	}
}