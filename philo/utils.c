/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 18:04:05 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/09/17 12:22:28 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	ft_isdigit(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
	}
	return (1);
}

long int	ft_atol(char *str)
{
	int			i;
	long int	neg;
	long int	res;

	i = 0;
	neg = 1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (neg * res);
}

int	ft_error(char *s, t_all *all)
{
	printf("%s\n", s);
	if (all)
		ft_free(all);
	return (-1);
}

void	ft_free(t_all *all)//entendre funcio
{
	int	i;

	free(all->philo);
	i = -1;
	while (++i < all->num_philo)
		pthread_mutex_destroy(&all->forks[i]);
	pthread_mutex_destroy(&all->print);
	pthread_mutex_destroy(&all->update);
	pthread_mutex_destroy(&all->done);
	free(all->forks);
}

long int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
