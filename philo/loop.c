/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:31:30 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/09/16 13:51:23 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

// Funció que simula el comportament d'un filòsof
void	*philosophers(t_philo *philo)
{
	long long int	time;
	int				eat_rep;
	// int 			flag;
	int				dead_flag;

	eat_rep = 1;
	// flag = 1;
	dead_flag = 1;
	time = 0;
	if ((philo->num & 1) == 1)//vol dir que es impar, estil bits
		usleep(philo->all->t_eat / 2);//*1000

	//cal qe tots els filo mengin eat_rep, no nomes el primer philo 
	while (!cheak_dead(philo, 1))//si retorna 1 es que un philo l'ha palmat pt ja no entra
	{
		//temps
		printf("passa per temps\n");
		time = get_time() + philo->all->t_eat;
		philo->last_ate = get_time();

		// Agafa els coberts
		// printf("r fork = %d \n", philo->r_fork);
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
		// if (flag == 1)
		// 	eat_rep = 1;
			
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

int			cheak_dead(t_philo *philo, int i)
{
	long long int	time;

	pthread_mutex_lock(&philo->all->update);
	time = get_time() - philo->all->t_eat;
	if (time > philo->all->t_die)
	{
		pthread_mutex_lock(&philo->all->palmar);
		philo->dead = 1;
		pthread_mutex_unlock(&philo->all->palmar);
		if (i == 1)
			printf("%lli %d is dead\n", time, philo->num);//print_status(philo, "died");
		pthread_mutex_unlock(&philo->all->update);
		return (1);
	}
	pthread_mutex_unlock(&philo->all->update);
	return (0);
}