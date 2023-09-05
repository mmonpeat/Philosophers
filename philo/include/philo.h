/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 20:00:14 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/09/05 12:10:31 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct	s_all	t_all;

typedef struct s_philo
{
	t_all			*all;
	pthread_t		thread_id;//numero especific per cada philosof
	int				num;//el numero vull dir 1, 2 o 3 
	int				r_fork;//fork dreta
	int				l_fork;//fork esquerra
	long long int	last_ate;
	
}				t_philo;

struct s_all 
{
	long int		num_philo;
	pthread_mutex_t	*forks;//array amb dues forks
	long int		t_die;
	long int		t_eat;
	long int		t_sleep;
	int				eat_times;
	t_philo			*philo;//apunta a l'estruct de dalt
};

//STARTS 
int			ft_start(int ac, char **av, t_all *all);
int			start_philo(t_all *all);
void		*philosophers(t_philo *philo);
// void		print_mutex(t_philo *philo, int num);
//AUXILIARS
long int	ft_atol(char *str);

//GESTIO TEMPS
long int	get_time(void);

#endif