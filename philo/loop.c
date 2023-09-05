/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:31:30 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/09/05 11:47:46 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

// Funció que simula el comportament d'un filòsof
void	*philosophers(t_philo *philo)
{
	long long int	time;
	int				eat_rep;
	int 			flag;
	int				dead_flag;

	eat_rep = 1;
	flag = 1;
	dead_flag = 1;
	if (philo->all->eat_times)
	{
		eat_rep = philo->all->eat_times;//passa per qui la quant de philo
		flag = 0;
	}
	while (eat_rep > 0)//cal qe tots els filo mengin eat_rep, no nomes el primer philo 
	{
		//temps
		printf("passa per temps\n");
		time = get_time() + philo->all->t_eat;
		philo->last_ate = get_time();

		// Agafa els coberts
		// printf("r fork = %d \n", philo->r_fork);
		if ((philo->num & 1) == 1)//vol dir que es impar, estil bits
			usleep(philo->all->t_eat / 2);//200 hauria ->  philo->all->t_eat
		pthread_mutex_lock(&philo->all->forks[philo->r_fork]);//dreta
		printf("%lli %d has taken a fork\n", time, philo->num);
		pthread_mutex_lock(&philo->all->forks[philo->l_fork]);//esquerra
		printf("%lli %d has taken a fork\n", time, philo->num);

		//com es una rodona, potser dos philosophers han pillat la mateixa
		if (philo->l_fork == philo->r_fork)
		{
			pthread_mutex_unlock(&philo->all->forks[philo->r_fork]);
		}
		printf("%lli %d is eating\n", time, philo->num);

		//pthread_mutex_unlock(&philo->all->forks);//aquesta crec que no cal
		if (dead_flag == 0)
			break;
		if ((time - philo->last_ate) >= philo->all->t_die)
		{
			printf("%lli %d is dead\n", time, philo->num);
			dead_flag = 0;
			break;
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
			printf("%lli %d is sleeping\n", time, philo->num);
			usleep(philo->all->t_sleep);//200 hauria -> philo->all->t_sleep
			printf("%lli %d is thinking\n", time, philo->num);
		}

	}
	//free(philo->all->forks);
	//free(philo->all->philo);
	return (NULL);
}

// void	print_mutex(t_philo *philo, int num)
// {
// 	if (num == 1)//fork r
// 	{
// 		pthread_mutex_lock(&philo->all->forks[philo->r_fork]);//dreta
// 		printf("%lli %d has taken a fork\n", time, philo->num);
// 		pthread_mutex_unlock(&philo->all->forks[philo->r_fork]);
// 	}
// 	else if (num == 2)
// 	{
// 		pthread_mutex_lock(&philo->all->forks[philo->l_fork]);//esquerra
// 		printf("%lli %d has taken a fork\n", time, philo->num);
// 		pthread_mutex_unlock(&philo->all->forks[philo->l_fork]);
// 	}
// }