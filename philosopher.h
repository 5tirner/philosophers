/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:23:23 by zasabri           #+#    #+#             */
/*   Updated: 2023/03/22 09:24:13 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

typedef	struct s_infos
{
	int	philo_nbr;
	int	to_eat;
	int	to_die;
	int	to_sleep;
	int	repeat_eat;
	int	timer;
}	t_infos;

int		ft_atoi(const char *str);

#endif