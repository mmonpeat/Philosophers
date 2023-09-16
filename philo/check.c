#include "include/philo.h"

int	valid_args(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac <= 4 || ac >= 5)
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
	time = get_time() - philo->all->t_eat;
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