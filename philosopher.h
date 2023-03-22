/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:23:23 by zasabri           #+#    #+#             */
/*   Updated: 2023/03/22 18:26:08 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				pos;
	int				right;
	int				left;
	unsigned long	eat;
	int				last_meal;
	struct s_infos	*info;
}	t_philo;

typedef struct s_infos
{
	int				philo_nbr;
	int				to_eat;
	int				to_die;
	int				to_sleep;
	int				repeat_eat;
	int				timer;
	t_philo			philo[1000];
	pthread_mutex_t	fork[1000];
	pthread_mutex_t	meal;
	pthread_mutex_t	out;
}	t_infos;

int		ft_atoi(const char *str);
void	creat_philosophers(t_infos *info);
int		manage_mutex(t_infos *info);

#endif