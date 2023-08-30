/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 20:00:14 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/08/30 19:30:39 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct	s_all	t_all;

typedef struct s_philo
{
	t_all			*all;
	pthread_t		thread_id;
	int				num;
	int				r_fork;
	int				l_fork;
}				t_philo;

struct s_all 
{
	int				num_philo;
	pthread_mutex_t	*forks;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				eat_times;
	t_philo			*philo;
};

//STARTS 
int		ft_start(int ac, char *av, t_all *all);
void	start_all(t_all *all);
void	start_philo(t_all *all);
void	*philoso(t_philo *philo);

//AUXILIARS
int		ft_atoi(const char *str);

#endif