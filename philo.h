/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 19:32:38 by zasabri           #+#    #+#             */
/*   Updated: 2023/04/13 14:57:06 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_infos
{
	int				ph_nb;
	unsigned long	eat;
	unsigned long	sleep;
	unsigned long	die;
	unsigned long	m_nbr;
	int				right;
	int				left;
	int				pos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
}	t_infos;

unsigned long	ft_atoi(const char *str);

#endif