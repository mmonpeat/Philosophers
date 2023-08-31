/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:31:30 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/08/31 13:30:50 by mmonpeat         ###   ########.fr       */
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
		// printf("r fork = %d \n", philo->r_fork);
		if ((philo->num & 1) == 1)
			usleep(200);//hauria des ser una mica mes de un milisegon no 200
		pthread_mutex_lock(&philo->all->forks[philo->r_fork]);//dreta
		printf("Filòsof %d has taken a fork\n", philo->num);

		// printf("l fork = %d \n", philo->l_fork);
		if ((philo->num & 1) == 1)
			usleep(200);//hauria des ser una mica mes de un milisegon no 200
		pthread_mutex_lock(&philo->all->forks[philo->l_fork]);//esquerra
		printf("Filòsof %d has taken a fork\n", philo->num);

		//com es una rodona, potser dos philosophers han pillat la mateixa
		if (philo->l_fork == philo->r_fork)
		{
			pthread_mutex_unlock(&philo->all->forks[philo->r_fork]);
		}
		printf("Filòsof %d menjant...\n", philo->num);
		usleep(300);  // Simula temps de menjar massa temps

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
