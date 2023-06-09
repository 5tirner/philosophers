/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:23:23 by zasabri           #+#    #+#             */
/*   Updated: 2023/04/20 04:58:00 by zasabri          ###   ########.fr       */
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
	time_t			t_zero;
	int				all_eat;
	int				checker;
	pthread_mutex_t	*fork;
	pthread_mutex_t	write;
	pthread_mutex_t	increment;
}					t_infos;

unsigned long	ft_atoi(const char *str);
int				check_input(char **av);
int				initialize_input(char **argv, int argc, t_infos *info);
int				stop(t_infos *info);
time_t			time_generate(void);
void			take_forks(t_infos *info, pthread_mutex_t *r,
					pthread_mutex_t *l, int p);
void			take_break(int ts);
int				creat_threads(t_infos *info, pthread_t *philo);
void			*philosopher(void *arg);

#endif