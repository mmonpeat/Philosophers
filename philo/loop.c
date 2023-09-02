/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:31:30 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/09/02 11:11:02 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

// Funció que simula el comportament d'un filòsof
void	*philosophers(t_philo *philo)
{
	int	eat_rep;
	int flag;

	eat_rep = 1;
	flag = 1;
	if (philo->all->eat_times)
	{
		eat_rep = philo->all->eat_times;//passa per qui la quant de philo
		flag = 0;
	}
	while (eat_rep > 0)//cal qe tots els filo mengin eat_rep, no nomes el primer philo 
	{
		// Agafa els coberts
		// printf("r fork = %d \n", philo->r_fork);
		if ((philo->num & 1) == 1)//vol dir que es impar, estil bits
			usleep(200);//pq es el temps que triga a menjar
		pthread_mutex_lock(&philo->all->forks[philo->r_fork]);//dreta
		printf("%d has taken a fork\n", philo->num);

		// printf("l fork = %d \n", philo->l_fork);
		if ((philo->num & 1) == 1)
			usleep(200);//hauria des ser una mica mes de un milisegon no 200 
		pthread_mutex_lock(&philo->all->forks[philo->l_fork]);//esquerra
		printf("%d has taken a fork\n", philo->num);

		//com es una rodona, potser dos philosophers han pillat la mateixa
		if (philo->l_fork == philo->r_fork)
		{
			pthread_mutex_unlock(&philo->all->forks[philo->r_fork]);
		}
		printf("%d is eating\n", philo->num);
		usleep(300);

		// unlock, deixa les dues forquilles usades
		pthread_mutex_unlock(&philo->all->forks[philo->r_fork]);
		pthread_mutex_unlock(&philo->all->forks[philo->l_fork]);

		printf("%d is sleeping\n", philo->num);
		usleep(100);
		
		printf("%d is thinking\n", philo->num);
		usleep(100);
		eat_rep--;
		if (flag == 1)
			eat_rep = 1;
	}
	return (NULL);
}
