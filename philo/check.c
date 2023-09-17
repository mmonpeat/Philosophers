#include "include/philo.h"

int	valid_args(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac < 5 || ac > 6)
		return (0);
	while (++i < ac)
	{
		if (!ft_isdigit(av[i]))
			return (0);
		else if (ft_atol(av[i]) <= 0 || ft_atol(av[i]) < INT_MIN \
			|| ft_atol(av[i]) > INT_MAX)
			return (0);
	}
	return (1);
}

int	check_dead(t_philo *philo, int i)
{
	long long int	time;

	pthread_mutex_lock(&philo->all->update);
	time = get_time() - philo->last_ate;
	if (time > philo->all->t_die)
	{
		pthread_mutex_lock(&philo->all->done);
		philo->dead = 1;
		pthread_mutex_unlock(&philo->all->done);
		if (i == 1)
			print_status(philo, "died");
		pthread_mutex_unlock(&philo->all->update);
		return (1);
	}
	pthread_mutex_unlock(&philo->all->update);
	return (0);
}

int	join_philo(t_all *all)
{
	int	i;

	while (all->any_dead == 0)
	{
		i = -1;
		while (++i < all->num_philo && !check_dead(&all->philo[i], 1))//comprova que cap philo estigi mort
			;
		if (i != all->num_philo)//si un ha mort
		{
			pthread_mutex_lock(&all->done);
			all->any_dead = 1;//1 indica que un l'ha palmat
			pthread_mutex_unlock(&all->done);
		}
		if (philo_finish(all))
		{
			pthread_mutex_lock(&all->print);
			printf("everyone finished eating\n");
			pthread_mutex_unlock(&all->print);
			break ;
		}
	}
	i = -1;
	while (++i < all->num_philo)
		pthread_join(all->philo[i].thread_id, NULL);
	return (1);
}

int	philo_finish(t_all *all)//comprova si tot han acabat de menjar
{
	int	i;

	i = -1;
	while (++i < all->num_philo)
	{
		pthread_mutex_lock(&all->done);
		if (!all->philo[i].done)//no han acabat
		{
			pthread_mutex_unlock(&all->done);
			return (0);
		}
		pthread_mutex_unlock(&all->done);
	}
	return (1);//retorna 1 (és a dir, tots els filòsofs han acabat de menjar)
}
