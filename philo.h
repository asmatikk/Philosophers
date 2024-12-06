/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:27:06 by afrikach          #+#    #+#             */
/*   Updated: 2024/12/05 16:48:01 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>

# define MAX_PHILOS 200

typedef struct s_philo
{
	int id;
	pthread_t thread;
	int left_fork;
	int	right_fork;
	struct s_table *table;
}		t_philo;

typedef struct s_table
{
	int	nb_philo;
	pthread_mutex_t *forks;
	int	t_to_die;
	int	t_to_eat;
	int	t_to_sleep;
	t_philo	*philo;
}	t_table;

int		check_input(int ac, char **av);
void	init_struct(t_table *table, char **av);
int		ft_atoi(const char *str);
void	*philo_routine(void *arg);

#endif
