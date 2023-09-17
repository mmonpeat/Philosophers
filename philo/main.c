/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 19:59:37 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/09/17 12:45:17 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	main(int ac, char **av)
{
	t_all	all;

	//filosophers
	int	i;

	i = 0;
	if (!valid_args(ac, av))
		return (ft_error("ERROR\nPlease enter 4 or 5 positive integers", NULL));
	if (ft_start(av, &all) == -1)
		return (ft_error("ERROR\nCould not allocate memory", &all));
	// printf("ha passat ft_start, i start_philo\n");
	create_threads(&all);
	// printf("ha passat crear fils\n");
	join_philo(&all);
	ft_free(&all);
	return (0);
}

int	ft_start(char **av, t_all *all)
{
	all->num_philo = ft_atol(av[1]);
	all->t_die = ft_atol(av[2]);
	all->t_eat = ft_atol(av[3]);
	all->t_sleep = ft_atol(av[4]);
	all->eat_times = -1;//1r cal inicialitzar eat_times per si no existeix
	if (av[5])//si existeix el modifiques pel que t'han passat
		all->eat_times = ft_atol(av[5]);
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

	i = -1;
	all->philo = malloc(sizeof(t_philo) * all->num_philo);
	if (!all->philo)
		return (-1);
	while (i++ < all->num_philo)
	{
		all->philo[i].all = all;
		all->philo[i].num = i + 1;
		all->philo[i].ate_count = 0;
		all->philo[i].last_ate = get_time();
		all->philo[i].dead = 0;
		all->philo[i].l_fork = i;
		all->philo[i].r_fork = i + 1;
		if (i == all->num_philo - 1)//si es lultim fer q la fork sigui la 0
			all->philo[i].r_fork = 0;
	}
	all->forks = malloc(sizeof(pthread_mutex_t) * all->num_philo);
	if (!all->forks)
		return (-1);
	i = -1;
	while (i++ < all->num_philo)
		pthread_mutex_init(&all->forks[i], NULL);
	return (0);
}

int	create_threads(t_all *all)
{
	int		i;

	i = -1;
	pthread_mutex_lock(&all->update);//nomes pot crearr un philosoph a la vagada
	while (++i < all->num_philo)
		pthread_create(&all->philo[i].thread_id, NULL, \
		(void *)philosophers, &all->philo[i]);
	pthread_mutex_unlock(&all->update);
	return (0);
}
