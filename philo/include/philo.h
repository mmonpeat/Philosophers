/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 20:00:14 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/09/17 12:09:43 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
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
	int				done;//marcador que indica si un filòsof ha acabat de menjar o no.
	long long int	last_ate;
	int				dead;//esta o no mort
	
}				t_philo;

struct s_all 
{
	long int		start;
	long int		num_philo;
	long int		t_die;
	long int		t_eat;
	long int		t_sleep;
	int				eat_times;
	int				any_dead;
	int				finished_count;
	pthread_mutex_t	*forks;//array amb dues forks
	pthread_mutex_t	print;
	pthread_mutex_t	update;
	pthread_mutex_t	done;
	t_philo			*philo;//apunta a l'estruct de dalt
};

//STARTS 
int			ft_start(char **av, t_all *all);
int			start_philo(t_all *all);
int			create_threads(t_all *all);

//loop
void		*philosophers(t_philo *philo);
int			eat(t_philo *philo);
void		sleep_and_think(t_philo *philo);
int			print_status(t_philo *philo, char *s);

//ckeck
int			valid_args(int ac, char **av);
int			check_dead(t_philo *philo, int i);
int			join_philo(t_all *all);
int			philo_finish(t_all *all);

//utils
int			ft_isdigit(char *s);
long int	ft_atol(char *str);
int			ft_error(char *s, t_all *all);
void		ft_free(t_all *all);
long int	get_time(void);

#endif