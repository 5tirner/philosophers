/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 19:32:38 by zasabri           #+#    #+#             */
/*   Updated: 2023/04/05 00:05:06 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philos
{
	int				right;
	int				left;
	int				pos;
	int				last_meal;
	struct	s_infos	*infos;
	
}	t_philos;

typedef struct s_infos
{
	unsigned long	ph_nb;
	unsigned long	eat;
	unsigned long	sleep;
	unsigned long	die;
	unsigned long	m_nbr;
	t_philos		*philo;
	t_philos		*forks;
}	t_infos;

unsigned long	ft_atoi(const char *str);

#endif