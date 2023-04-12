#include "philo.h"

int	start_initialize(t_infos *info, char **av, int ac)
{
	info->ph_nb = ft_atoi(av[1]);
	if (info->ph_nb > 200 || info->ph_nb <= 0)
		return (printf("1 <= philo_nbr <= 200\n"));
	info->die = ft_atoi(av[2]);
	info->eat = ft_atoi(av[3]);
	info->sleep = ft_atoi(av[4]);
	if (info->die < 60 || info->eat < 60 || info->sleep < 60)
		return (printf("Enter times more or equal 60ms\n"));
	if (ac == 5)
		info->m_nbr = -1;
	else
	{
		info->m_nbr = ft_atoi(av[5]);
		if (info->m_nbr <= 0)
			return (printf("Enter meal nbr more than 0\n"));
	}
	return (0);
}

int	check_this_arg(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if ((av[i] != '+')
			&& (av[i] < '0' || av[i] > '9'))
			return (1);
		if (i != 0 && (av[i] < '0' || av[i] > '9'))
			return (1);
		i++;
	}
	return (0);
}

int	check_input(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (check_this_arg(av[i]))
			return (printf("Problem here: %s\n", av[i]));
		i++;
	}	
	return (0);
}

void *philosopher(void *arg)
{
	t_infos	*info;
	int		id;
	int		left_fork;
	int		right_fork;
	
	id = *((int *) arg);
	left_fork = id;
	right_fork = (id + 1) % info->ph_nb;
	printf("here\n");
	while (1)
	{
		printf("Philosopher %d is taken a fork\n", id);
		pthread_mutex_lock(&info->forks[left_fork]);
		pthread_mutex_lock(&info->forks[right_fork]);     
		printf("Philosopher %d is eating\n", id);
		sleep(info->eat);
		printf("Philosopher %d is sleeping\n", id);
		sleep(info->sleep);
		pthread_mutex_unlock(&info->forks[left_fork]);
		pthread_mutex_unlock(&info->forks[right_fork]);
	}
} 

int main(int ac, char **av)
{
	int i;
	t_infos		info;
	pthread_t	*threads;
	int			*ids;
	if (ac == 5 || ac == 6)
	{
		if (check_input(av))
			return (1);
		if (start_initialize(&info, av, ac))
			return (1);
		//printf("%d\n", info.ph_nb);
		info.forks = malloc(sizeof(pthread_mutex_t) * info.ph_nb);
		ids = malloc(sizeof(int) * info.ph_nb);
		i = -1;
		//printf("here\n");
		while (++i < info.ph_nb)
		{
			if (pthread_mutex_init(&info.forks[i], NULL))
				return (printf("Somthin wrong happen\n"));
		}
		//printf("here\n");
		threads = malloc(sizeof(pthread_t) * info.ph_nb);
		i = -1;
		while (++i < info.ph_nb)
		{
			printf("here %d\n", i);
			ids[i] = i;
			if (pthread_create(&threads[i], NULL, philosopher, (void *) &ids[i]))
				return (printf("Thread creat failed\n"));
		}
		i = -1;
		while (++i < info.ph_nb)
		{
			if (pthread_join(threads[i], NULL))
				return (printf("Somthing wrong happen\n"));
		}
		i = -1;
		while (++i < info.ph_nb)
		{
			if (pthread_mutex_destroy(&info.forks[i]))
				return (printf("Somthing wrong happen\n"));
		}
	}
}