/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 19:59:37 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/08/30 18:40:03 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

// Funció que simula el comportament d'un filòsof
void	*philoso(t_philo *philo)
{
	int	flag;

	flag = 0;
	while (flag < 10) 
	{
		// Agafa els coberts
		printf("r fork = %d \n", philo->r_fork);
		pthread_mutex_lock(&philo->all->forks[philo->r_fork]);//dreta
		printf("Filòsof %d has taken a fork\n", philo->num);
		
		printf("l fork = %d \n", philo->l_fork);
		pthread_mutex_lock(&philo->all->forks[philo->l_fork]);//esquerra
		printf("Filòsof %d has taken a fork\n", philo->num);

		//com es una rodona, potser dos philosophers han pillat la mateixa
		if (philo->l_fork == philo->r_fork)
		{
			pthread_mutex_unlock(&philo->all->forks[philo->r_fork]);
		}
		printf("Filòsof %d menjant...\n", philo->num);
		usleep(300);  // Simula temps de menjar

		// unlock, deixa les dues forquilles usades
		pthread_mutex_unlock(&philo->all->forks[philo->r_fork]);
		pthread_mutex_unlock(&philo->all->forks[philo->l_fork]);
		printf("Filòsof %d ha acabat de menjar.\n", philo->num);

		printf("Filòsof %d dormint...\n", philo->num);
		usleep(100);// Simula temps de dormir
		
		printf("Filòsof %d pensant...\n", philo->num);
		usleep(100);// Simula temps de pensament
		flag++;
	}
	return (NULL);
}

void	start_all(t_all *all)
{
	all->eat_times = 2;
	all->num_philo = 3;
	all->t_die = 800;
	all->t_eat = 200;
	all->t_sleep = 200;
}

void	start_philo(t_all *all)
{
	int i = 0;
	all->forks = malloc(sizeof(pthread_mutex_t) * 3);
	all->philo = malloc(sizeof(t_philo) * 3);
	while (i < all->num_philo)
	{
		if (i == all->num_philo - 1)
			all->philo[i].r_fork = 0;
		else
			all->philo[i].r_fork = i + 1;
		all->philo[i].all = all;
		all->philo[i].num = i + 1;
		all->philo[i].l_fork = i;
		//si es lultim fer q la fork sigui la 0
		pthread_mutex_init(&all->forks[i], NULL);
		printf("philo %d l fork = %d \n", all->philo[i].num, all->philo[i].l_fork);
		printf("philo %d r fork = %d \n", all->philo[i].num, all->philo[i].r_fork);
		i++;
	}
}

int main()
{
	t_all	all;

	//filosophers
	int i = 0;
	start_all(&all);
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


// int	ft_start(int ac, char *av, t_all *all)
// {
// 	if (ac == 4 || ac == 5)
// 	{
// 		all->num_philo = ft_atoi(&av[1]);
// 		all->t_die = ft_atoi(&av[2]);
// 		all->t_eat = ft_atoi(&av[3]);
// 		all->t_sleep = ft_atoi(&av[4]);
// 		if (av[6])
// 			all->eat_times = ft_atoi(&av[6]);
// 	}
// 	else
// 	{
// 		printf("Cal que passis els seguents arguments: \n");
// 		printf("1. Numero de philosophers\n");
// 		printf("2. El temps que triguen en morir aquests\n");
// 		printf("3. El temps que estant menjant aquests\n");
// 		printf("4. El temps que estant dormint aquests\n");
// 	}
// 	return (0);
// }


// int main(int ac, char **av)
// {
// 	t_all		*all;

// 	all = NULL;

// 	ft_start(ac - 1, *av, all);
// 	return (1);
// }

// int	ft_start(int ac, char *av, t_all *all)
// {
// 	if (ac == 4 || ac == 5)
// 	{
// 		all->num_philo = ft_atoi(&av[1]);
// 		all->t_die = ft_atoi(&av[2]);
// 		all->t_eat = ft_atoi(&av[3]);
// 		all->t_sleep = ft_atoi(&av[4]);
// 		if (av[6])
// 			all->eat_times = ft_atoi(&av[6]);
// 		fils(all);
// 	}
// 	else
// 	{
// 		printf("Cal que passis els seguents arguments: \n");
// 		printf("1. Numero de philosophers\n");
// 		printf("2. El temps que triguen en morir aquests\n");
// 		printf("3. El temps que estant menjant aquests\n");
// 		printf("4. El temps que estant dormint aquests\n");
// 	}
// 	return (0);
// }

// void fils(t_all *all)
// {
// 	printf("Before Thread\n");
// 	pthread_create(&all->thread_id, NULL, hola, all);
// 	pthread_join(all->thread_id, NULL);
// 	printf("After Thread\n");
// 	exit(0);
// }

// void *hola(t_all *all)
// {
// 	sleep(1);
// 	printf("he creat un fil: \n");
// 	return (NULL);
// }