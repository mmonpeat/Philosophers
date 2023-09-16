/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:31:30 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/09/16 19:29:30 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

// Funció que simula el comportament d'un filòsof
void	*philosophers(t_philo *philo)
{
	if ((philo->num & 1) == 1)//vol dir que es impar, estil bits
		usleep(philo->all->t_eat / 2);//*1000
	while (!check_dead(philo, 1))//si retorna 1 es que un philo l'ha palmat pt ja no entra
	{
		if (eat(philo))
			break ;
		if (philo->ate_count == philo->all->eat_times)
		{
			pthread_mutex_lock(&philo->all->done);
			philo->done = 1;
			pthread_mutex_unlock(&philo->all->done);
			break ;
		}
		if (!check_dead(philo, 0))
			sleep_think(philo);
		pthread_mutex_lock(&philo->all->done);
		if (philo->all->any_dead)
		{
			pthread_mutex_unlock(&philo->all->done);
			break ;
		}
		pthread_mutex_unlock(&philo->all->done);
	}
	return (NULL);
}

int	check_dead(t_philo *philo, int i)
{
	long long int	time;

	pthread_mutex_lock(&philo->all->update);
	time = get_time() - philo->all->t_eat;
	if (time > philo->all->t_die)
	{
		pthread_mutex_lock(&philo->all->done);
		philo->dead = 1;
		pthread_mutex_unlock(&philo->all->done);
		if (i == 1)
			printf("%lli %d is dead\n", time, philo->num);//print_status(philo, "died");
		pthread_mutex_unlock(&philo->all->update);
		return (1);
	}
	pthread_mutex_unlock(&philo->all->update);
	return (0);
}

int	eat(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(&philo->all->forks[philo->r_fork]);//dreta
	printf("%d has taken a fork\n", philo->num);
	if (philo->l_fork == philo->r_fork)//com es una rodona, potser dos philosophers han pillat la mateixa
	{
		pthread_mutex_unlock(&philo->all->forks[philo->r_fork]);
	}
	pthread_mutex_lock(&philo->all->forks[philo->l_fork]);//esquerra
	printf("%d has taken a fork\n", philo->num);
	pthread_mutex_lock(&philo->all->update);
	printf("%d is eating\n", philo->num);
	time = get_time() + philo->all->t_eat;
	philo->last_ate = get_time();
	pthread_mutex_unlock(&philo->all->update);
	while (get_time() <= time && !check_dead(philo, 0))
		usleep(200);
	philo->ate_count++;
	pthread_mutex_unlock(&philo->all->forks[philo->r_fork]);// unlock, deixa les dues forquilles usades
	pthread_mutex_unlock(&philo->all->forks[philo->l_fork]);
	return (0);
}
