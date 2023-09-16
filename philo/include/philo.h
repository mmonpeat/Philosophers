/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 20:00:14 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/09/16 19:26:26 by mmonpeat         ###   ########.fr       */
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
	int				ate_count;
	int				done;
	long long int	last_ate;
	int				dead;//esta o no mort
	
}				t_philo;

struct s_all 
{
	long int		num_philo;
	long int		t_die;
	long int		t_eat;
	long int		t_sleep;
	int				eat_times;
	int				any_dead;
	pthread_mutex_t	*forks;//array amb dues forks
	pthread_mutex_t	print;
	pthread_mutex_t	update;
	pthread_mutex_t	done;
	t_philo			*philo;//apunta a l'estruct de dalt
};

//STARTS 
int			ft_start(int ac, char **av, t_all *all);
int			start_philo(t_all *all);
int			create_threads(t_all *all);

//loop
void		*philosophers(t_philo *philo);
int			check_dead(t_philo *philo, int i);
int			eat(t_philo *philo);
// void		print_mutex(t_philo *philo, int num);
//AUXILIARS
long int	ft_atol(char *str);

//GESTIO TEMPS
long int	get_time(void);

#endif