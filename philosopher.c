/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:20:55 by zasabri           #+#    #+#             */
/*   Updated: 2023/03/17 16:28:50 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "philosopher.h"

// unsigned long	x;

// void	eating(t_time *times)
// {
// 	int	j;
	
// 	j = 0;
// 	printf("philo %d start eating in the time %lu\n", times->i, x);
// 	while (j < times->time_to_eat)
// 	{
// 		pthread_mutex_lock(&times->mutex);
// 		j++;
// 		x++;
// 		pthread_mutex_unlock(&times->mutex);
// 	}
// 	printf("philo %d ends in the time: %lu\n", times->i, x);
// }

// void	sleeping(t_time *times)
// {
// 	int	j;
	
// 	j = 0;
// 	printf("philo %d start sleeping in the time %lu\n", times->i, x);
// 	while (j < times->time_to_sleep)
// 	{
// 		pthread_mutex_lock(&times->mutex);
// 		j++;
// 		x++;
// 		pthread_mutex_unlock(&times->mutex);
// 	}
// 	printf("philo %d weak uo at time: %lu\n", times->i, x);
// }

// // void	check_death(t_time *times)
// // {
		
// // }

// void	*cyrcle(void *times)
// {
// 	t_time	*time;
	
// 	time = (t_time *)times;
// 	pthread_mutex_init(&time->mutex, NULL);
// 	printf("Philo %d takes a fork\n", time->i);
// 	eating(time);
// 	sleeping(time);
// 	pthread_mutex_destroy(&time->mutex);
// 	//check_death(&time->mutex);
// 	return (0);
// }

// // pthread_t	creat_philo(pthread_t *philo, t_time times, int philo_nbr)
// // {
// // 	while (times.i < philo_nbr)
// // 	{
// // 		if (pthread_create(&philo[times.i], NULL, &cyrcle, &times))
// // 		{
// // 			write(2, "Problem with thread creation\n", 29);
// // 			return (1);
// // 		}
// // 		times.i++;
// // 	}
// // 	return (philo);
// // }
// int main(int ac, char **av)
// {
// 	t_time		times;
// 	pthread_t	*philo;
// 	int			philo_nbr;
// 	if (ac >= 4)
// 	{
// 		philo_nbr = ft_atoi(av[1]);
// 		philo = malloc(philo_nbr);
// 	 	times.time_to_die = ft_atoi(av[2]);
// 		times.time_to_eat = ft_atoi(av[3]);
// 		times.time_to_sleep = ft_atoi(av[4]);
// 		times.i = 1;
// 		//create_philos(philo, times.i, philo_nbr);
// 		while (times.i <= philo_nbr)
// 		{
// 			if (pthread_create(&philo[times.i], NULL, &cyrcle, &times))
// 			{
// 				printf("Thread created is failed\n");
// 				return (1);
// 			}
// 			if (pthread_join(philo[times.i], NULL))
// 			{
// 				printf("Somthing unexpected is happen\n");
// 				return (1);
// 			}
// 			times.i++;
// 		}
// 	}
// 	else
// 	{
// 		printf("Invalid number of argements\n");
// 		return (1);
// 	}
// }

#include "philosopher.h"

unsigned long	x;

void	eating(t_time *times)
{
	int	j;
	
	j = 0;
	//printf("befor\n");
	printf("philo %d start eating in the time %lu\n", times->i, x);
	//printf("here1\n");
	while (j < times->time_to_eat)
	{
		pthread_mutex_lock(&times->mutex);
		j++;
		x++;
		pthread_mutex_unlock(&times->mutex);
	}
	printf("philo %d ends in the time: %lu\n", times->i, x);
}

void	sleeping(t_time *times)
{
	int	j;
	
	j = 0;
	printf("philo %d start sleeping in the time %lu\n", times->i, x);
	while (j < times->time_to_sleep)
	{
		pthread_mutex_lock(&times->mutex);
		j++;
		x++;
		pthread_mutex_unlock(&times->mutex);
	}
	printf("philo %d weak uo at time: %lu\n", times->i, x);
}

void	*cyrcle(void *times)
{
	t_time	*time;
	
	time = (t_time *)times;
	pthread_mutex_init(&time->mutex, NULL);
	printf("Philo %d takes a fork\n", time->i);
	eating(time);
	sleeping(time);
	pthread_mutex_destroy(&time->mutex);
	return (0);
}

int main(int ac, char **av)
{
	t_time		times;
	pthread_t	*philo;
	int			philo_nbr;
	if (ac >= 4)
	{
		philo_nbr = ft_atoi(av[1]);
		philo = malloc(philo_nbr);
	 	times.time_to_eat = ft_atoi(av[2]);
		times.time_to_sleep = ft_atoi(av[3]);
		times.i = 1;
		
		while (times.i <= philo_nbr)
		{
			if (pthread_create(&philo[times.i], NULL, &cyrcle, &times))
			{
				printf("Thread created is failed\n");
				return (1);
			}
			if (pthread_join(philo[times.i], NULL))
			{
				printf("Somthing unexpected is happen\n");
				return (1);
			}
			times.i++;
		}
	}
	else
	{
		printf("Invalid number of argements\n");
		return (1);
	}
}