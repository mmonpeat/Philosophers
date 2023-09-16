/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 19:59:37 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/09/16 21:40:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	main(int ac, char **av)
{
	t_all	all;

	//filosophers
	int i;

	i = 0;
	if (!valid_args(ac, av))
		return (ft_error("ERROR\nPlease enter 4 or 5 positive integers", NULL));
	if (ft_start(av, &all) == -1)
		return (ft_error("ERROR\nCould not allocate memory", &all));
	create_threads(&all);
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

int	ft_start(char **av, t_all *all)
{
	all->num_philo = ft_atol(av[1]);
	all->t_die = ft_atol(av[2]);
	all->t_eat = ft_atol(av[3]);
	all->t_sleep = ft_atol(av[4]);
	if (av[5])
		all->eat_times = ft_atol(av[5]);
	all->eat_times = -1;
	all->finished_count = 0;
	all->any_dead = 0;
	pthread_mutex_init(&all->print, NULL);
	pthread_mutex_init(&all->update, NULL);
	pthread_mutex_init(&all->done, NULL);
	all->start = get_time();
	if (start_philo(all) == -1)
		return (-1);
	return (0);
}

int	start_philo(t_all *all)//cal arregla aquesta funcio
{
	int	i;

	i = 0;
	all->philo = malloc(sizeof(t_philo) * all->num_philo);
	if (!all->philo)
		return (-1);
	all->forks = malloc(sizeof(pthread_mutex_t) * all->num_philo);
	if (!all->forks)
		return (-1);
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

int	create_threads(t_all *all)
{
	int		i;

	i = -1;
	pthread_mutex_lock(&all->update); //nomes pot crearr un philosoph a la vagada
	while (++i < all->num_philo)
		pthread_create(&all->philo[i].thread_id, NULL, \
		(void *)philosophers, &all->philo[i]);
	pthread_mutex_unlock(&all->update);
	return (0);
}
