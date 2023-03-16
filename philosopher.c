/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:20:55 by zasabri           #+#    #+#             */
/*   Updated: 2023/03/16 14:46:59 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

pthread_mutex_t	mutex;
unsigned long	x;

void	*sleeping(void *time_to_sleep)
{
	int	i = 0;
	int	*t = (int *)time_to_sleep;

	while (i < *t)
	{
		pthread_mutex_lock(&mutex);
		i++;
		x++;
		pthread_mutex_unlock(&mutex);
	}
	return (0);
}

void	*eat(void *time_to_eat)
{
	int i = 0;
	int	*t = (int *)time_to_eat;
	while(i < *t)
	{
		pthread_mutex_lock(&mutex);
		i++;
		x++;
		//printf("%d", x);
		pthread_mutex_unlock(&mutex);
	}
	return (0);
}

int main(int ac, char **av)
{
	// pthread_t t1, t2;
	// //pthread_mutex_init(&mutex, NULL);
	// pthread_create(&t1, NULL, rt, NULL);
	// pthread_create(&t2, NULL, rt, NULL);
	// pthread_join(t1, NULL);
	// pthread_join(t2, NULL);
	// //pthread_mutex_destroy(&mutex);
	// printf("%d", x);
	if (ac >= 3)
	{
		t_time		times;
		int			k = atoi(av[1]);
		int 		p = atoi(av[2]);
		int			r = atoi(av[3]);
		pthread_t	philo[k];
		int			i;

		i = 1;
		pthread_mutex_init(&mutex, NULL);
		while (i <= k)
		{
			if (pthread_create(&philo[i], NULL, &eat, &p))
			{
				printf("Thread created is failed\n");
				return (1);
			}
			printf("philo number %d is eating\n", i);
			if (pthread_join(philo[i], NULL))
			{
				printf("Somthing wrog with this thread\n");
				return (1);
			}
			printf("This philo go to sleep at the time %lu\n", x);
			if (pthread_create(&philo[i], NULL, &sleeping, &r))
			{
				printf("Thread created is failed\n");
				return (1);
			}
			printf("this philo still sleeping..\n");
			if (pthread_join(philo[i], NULL))
			{
				printf("Somthing wrong with this philo\n");
				return (1);
			}
			i++;
		}
		printf("number of seconds that the philos need %lu", x);
		pthread_mutex_destroy(&mutex);
	}
	else
	{
		printf("Invalid number of argements\n");
		return (1);
	}
}