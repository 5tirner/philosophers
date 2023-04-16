/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:23:23 by zasabri           #+#    #+#             */
/*   Updated: 2023/04/16 23:21:14 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_infos
{
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				meals;
	int				id;
	int				philo_nbr;
	int				meals_nbr;
	time_t			*lastmeal;
	pthread_mutex_t	*fork;
	pthread_mutex_t	write;
	pthread_mutex_t	increment;
}					t_infos;

unsigned long	ft_atoi(const char *str);
int				check_input(char **av);
int				initialize_input(char **argv, int argc, t_infos *info);
int				stop(t_infos *info);
time_t			time_generate(void);

#endif