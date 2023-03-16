/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:00:42 by zasabri           #+#    #+#             */
/*   Updated: 2023/03/16 15:32:48 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

typedef struct s_philosopher
{
	int id; 
	pthread_t x;
}	philosopher;

int	z = 0;

void	*r1(void *x)
{
	philosopher *y = (philosopher *) x;
	int i = -1;
	while (++i < 10)
	{
		printf("HI X=%d : %d\n", y->id, z++);
		x++;
	}
	return 0;
}

int main()
{
	pthread_t t1;
	pthread_t t2;

	philosopher a[2];

	a[0].id = 0;
	a[1].id = 1;
	int i = 0;
	while (i < 2)
	{
		pthread_create (&a[i].x, NULL, r1, &a[i]);
		pthread_join(a[i].x, NULL);
		i++;
	}
	printf("hi %d\n", z);
	//while(1);
}