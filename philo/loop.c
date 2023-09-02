/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:31:30 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/09/02 18:03:07 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

// Funció que simula el comportament d'un filòsof
void	*philosophers(t_philo *philo)
{
	long long int	time;
	int				eat_rep;
	int 			flag;

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
			usleep(philo->all->t_eat / 2);//200 hauria ->  philo->all->t_eat
		pthread_mutex_lock(&philo->all->forks[philo->r_fork]);//dreta
		printf("%d has taken a fork\n", philo->num);
		pthread_mutex_lock(&philo->all->forks[philo->l_fork]);//esquerra
		printf("%d has taken a fork\n", philo->num);

		//com es una rodona, potser dos philosophers han pillat la mateixa
		if (philo->l_fork == philo->r_fork)
		{
			pthread_mutex_unlock(&philo->all->forks[philo->r_fork]);
		}
		printf("%d is eating\n", philo->num);
		time = get_time() + philo->all->t_eat;
		philo->last_ate = get_time();
		//pthread_mutex_unlock(&philo->all->forks);//aquesta crec que no cal
		if ((time - philo->last_ate) >= philo->all->t_die)
		{
			printf("%d is dead\n", philo->num);
			return(NULL);
		}
		else
			usleep(philo->all->t_eat);//300 hauria -> philo->all->t_eat
		
		// unlock, deixa les dues forquilles usades
		pthread_mutex_unlock(&philo->all->forks[philo->r_fork]);
		pthread_mutex_unlock(&philo->all->forks[philo->l_fork]);

		eat_rep--;//crec que caldria pujar-ho despres del unlock
		if (flag == 1)
			eat_rep = 1;
			
		//MOREN
		// if (get)
		if (eat_rep != 0)
		{
			printf("%d is sleeping\n", philo->num);
			usleep(philo->all->t_sleep);//200 hauria -> philo->all->t_sleep
			printf("%d is thinking\n", philo->num);
		}

	}
	//free(philo->all->forks);
	//free(philo->all->philo);
	return (NULL);
}
