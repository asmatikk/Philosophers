/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:26:51 by afrikach          #+#    #+#             */
/*   Updated: 2024/12/05 17:26:20 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// initialisation des structures pour les philos et de la table
// initialisation des forks (Mutex) et des philos
void init_struct(t_table *table, char **av)
{
	int	i;
	
	i = 0;
	table->nb_philo = ft_atoi(av[1]);
	table->t_to_die = ft_atoi(av[2]) * 1000;
	table->t_to_eat = ft_atoi(av[3]) * 1000;
	table->t_to_sleep = ft_atoi(av[4]) * 1000;
	table->philo = malloc(sizeof(t_philo) * table->nb_philo);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
	if(!table->forks || !table->philo)
		return ;
	while (i < table->nb_philo)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		table->philo[i].id = i;
		table->philo[i].left_fork = i;
		table->philo[i].right_fork = (i + 1) % table->nb_philo;
		i++;
	}
}



// void	*philo_routine(void *arg)
// {
//   	t_philo *philo;
	
// 	philo = (t_philo *)arg;
// 	arg->t
//     printf("Philosopher %d is thinking...\n", philo->id);
//     printf("Philosopher %d is eating with forks %d and %d.\n", philo->id, philo->left_fork, philo->right_fork);

//     printf("The table has %d philosophers.\n", philo->table->nb_philo);

//     return NULL;
// }
