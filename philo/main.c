/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 19:59:37 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/08/30 19:49:25 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int main(int ac, char  **av)
{
	t_all	all;

	//filosophers
	int i = 0;
	printf("hola");
	ft_start(ac - 1, *av, &all);
	// start_all(&all);
	start_philo(&all);
	while (i < 3)
	{
		pthread_create(&all.philo[i].thread_id, NULL, (void *)philoso, &all.philo[i]);
		i++;
	}
	while(1)
		;
	i = 0;
	while (i < 3)
	{
		pthread_join(all.philo[i].thread_id, NULL);
		i++;
	}

	i = 0;
	while (i < 3)
	{
		pthread_mutex_destroy(&all.forks[i]);
		i++;
	}
}

int	ft_start(int ac, char *av, t_all *all)
{
	if (ac == 4 || ac == 5)
	{
		printf("hola");
		all->num_philo = ft_atoi(&av[1]);
		all->t_die = ft_atoi(&av[2]);
		all->t_eat = ft_atoi(&av[3]);
		all->t_sleep = ft_atoi(&av[4]);
		if (av[5])
			all->eat_times = ft_atoi(&av[5]);
	}
	else
	{
		printf("Cal que passis els seguents arguments: \n");
		printf("1. Numero de philosophers\n");
		printf("2. El temps que triguen en morir aquests\n");
		printf("3. El temps que estant menjant aquests\n");
		printf("4. El temps que estant dormint aquests\n");
	}
	return (0);
}

// void	start_all(t_all *all)
// {
// 	all->eat_times = 2;
// 	all->num_philo = 3;
// 	all->t_die = 600;
// 	all->t_eat = 200;
// 	all->t_sleep = 200;
// }

void	start_philo(t_all *all)
{
	int i = 0;
	all->forks = malloc(sizeof(pthread_mutex_t) * 3);
	all->philo = malloc(sizeof(t_philo) * 3);
	while (i < all->num_philo)
	{
		//si es lultim fer q la fork sigui la 0
		if (i == all->num_philo - 1)
			all->philo[i].r_fork = 0;
		else
			all->philo[i].r_fork = i + 1;
		all->philo[i].all = all;
		all->philo[i].num = i + 1;
		all->philo[i].l_fork = i;
		pthread_mutex_init(&all->forks[i], NULL);
		// printf("philo %d l fork = %d \n", all->philo[i].num, all->philo[i].l_fork);
		// printf("philo %d r fork = %d \n", all->philo[i].num, all->philo[i].r_fork);
		i++;
	}
}

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		str++;
	}
	return (sign * res);
}
