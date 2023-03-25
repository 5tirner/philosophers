/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_generator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 19:56:13 by zasabri           #+#    #+#             */
/*   Updated: 2023/03/25 20:34:08 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	action_generator(t_infos *info, int pos, char *msg)
{
	pthread_mutex_lock(&info->action);
	if (!info->if_died)
		printf("%d %s", pos + 1, msg);
	pthread_mutex_unlock(&info->action);
}
