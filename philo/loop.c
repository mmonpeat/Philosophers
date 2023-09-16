/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:31:30 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/09/16 21:11:09 by marvin           ###   ########.fr       */
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
			sleep_and_think(philo);
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

int	eat(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(&philo->all->forks[philo->r_fork]);//dreta
	print_status(philo, "has taken a fork");
	if (philo->l_fork == philo->r_fork)//com es una rodona, potser dos philosophers han pillat la mateixa
	{
		pthread_mutex_unlock(&philo->all->forks[philo->r_fork]);
	}
	pthread_mutex_lock(&philo->all->forks[philo->l_fork]);//esquerra
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->all->update);
	print_status(philo, "is eating");
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
 
void		sleep_and_think(t_philo *philo)
{
	long long	time;

	print_status(philo, "is slepping");
	time = get_time() + philo->all->t_sleep;
	while (get_time() <= time && !check_dead(philo, 0))
		usleep(200);
	if (!check_dead(philo, 0))
		print_status(philo, "is thinking");
}

int	print_status(t_philo *philo, char *s)
{
	pthread_mutex_lock(&philo->all->print);
	pthread_mutex_lock(&philo->all->done);
	if (!philo->all->any_dead)
		printf("%04li\t%i\t%s\n", (get_time() - \
			philo->all->start), philo->num, s);//saber que fa aixo
	pthread_mutex_unlock(&philo->all->done);
	pthread_mutex_unlock(&philo->all->print);
	return (0);
}
