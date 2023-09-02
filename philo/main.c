/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 19:59:37 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/09/02 13:49:40 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int main(int ac, char  **av)
{
	t_all	all;

	//filosophers
	int i;

	i = 0;
	if (ft_start(ac - 1, av, &all) == -1)
		return (0);
	if (start_philo(&all) == -1)
		return (0);
	while (i < all.num_philo)
	{
		pthread_create(&all.philo[i].thread_id, NULL, (void *)philosophers, &all.philo[i]);
		i++;
	}
	i = 0;
	while (i < all.num_philo)
	{
		pthread_join(all.philo[i].thread_id, NULL);
		i++;
	}
	i = 0;
	while (i <= all.num_philo)
	{
		pthread_mutex_destroy(&all.forks[i]);
		i++;
	}
	i = 0;
	while (i < all.num_philo)
	{
		free(all.philo);
		// free(all.philo->l_fork);
		// free(all.philo->r_fork);
		free(&all.forks[i]);
		i++;
	}
	return (0);
}

int	ft_start(int ac, char **av, t_all *all)
{
	if (ac == 4 || ac == 5)
	{
		all->num_philo = ft_atol(av[1]);
		all->t_die = ft_atol(av[2]);
		all->t_eat = ft_atol(av[3]);
		all->t_sleep = ft_atol(av[4]);
		if (av[5])
			all->eat_times = ft_atol(av[5]);
		// no puc posar per defecte el valor de vegades que han de menjar
	}
	else
	{
		printf("Cal que passis els seguents arguments: \n");
		printf("1. Numero de philosophers\n");
		printf("2. El temps que triguen en morir aquests\n");
		printf("3. El temps que estant menjant aquests\n");
		printf("4. El temps que estant dormint aquests\n");
		return (-1);
	}
	return (0);
}

int		start_philo(t_all *all)
{
	int	i;

	i = 0;
	all->forks = malloc(sizeof(pthread_mutex_t) * all->num_philo);
	if (!all->forks)
		return (-1);
	all->philo = malloc(sizeof(t_philo) * all->num_philo);
	if (!all->philo)
	{
		free(all->forks);
		return (-1);//crec que hauria de retornar NULL no -1 pero llavors es complica
	}
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
	return (0);
}

long int	ft_atol(char *str)
{
	int			i;
	long int	neg;
	long int	res;

	i = 0;
	neg = 1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (neg * res);
}
