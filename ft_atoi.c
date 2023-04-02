/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 19:37:02 by zasabri           #+#    #+#             */
/*   Updated: 2023/03/31 20:07:13 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_sign(const char *str)
{
	int	sign;
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] == '+' || str[i] == '-')
		{
			if (str[i] == '+' && (str[i + 1] >= '0' && str[i + 1] <= '9'))
				sign = 1;
			else if (str[i] == '-' && (str[i + 1] >= '0' && str[i + 1] <= '9'))
				sign = -1;
			else
				return (0);
			i++;
		}
		i++;
	}
	return (sign);
}

int	ft_check_over(int sign)
{
	if (sign > 0)
		return (-1);
	return (0);
}

unsigned long	ft_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long		res;
	unsigned long		t;

	i = 0;
	sign = 1;
	res = 0;
	while (((str[i] >= 9 && str[i] <= 13) || (str[i] == 32)))
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		sign = ft_sign(str);
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9'))
	{
		t = res * 10 + str[i] - 48;
		if (t < res)
			return (ft_check_over(sign));
		res = t;
		i++;
	}
	return (res * sign);
}
