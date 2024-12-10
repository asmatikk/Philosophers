/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:26:51 by afrikach          #+#    #+#             */
/*   Updated: 2024/12/10 17:08:33 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philo_routine(void *arg)
{
    t_philo *philo;
	t_table *table;
		
	philo = (t_philo *)arg;
	table = philo->table;
	// int nb = table->nb_philo;
	while(1)
	{
		if(check_free_forks(philo, philo->id) == 1)
		{
			pthread_mutex_lock(table->forks[philo->left_fork]);
			pthread_mutex_lock(table->forks[philo->right_fork]);
			printf("philo %d is eating\n", philo->id);
			printf("philo %d a pris la fourchette %d et %d\n", philo->id, philo->left_fork, philo->right_fork);
			philo->id++;
			usleep(philo->table->t_to_eat);
			pthread_mutex_unlock(table->forks[philo->left_fork]);
			pthread_mutex_unlock(table->forks[philo->right_fork]);
			// Philosophe dort
			// printf("Philosopher %d is sleeping\n", philo->id);
			// usleep(philo->table->t_to_sleep);
		}
		else
			break;
        // Philosophe pense
        // printf("Philosopher %d is thinking\n", philo->id);
	}
    return (NULL);
}

int	main(int ac, char **av)
{
	t_table *table = NULL;
	
	if (check_input(ac, av) == 1)
		return (printf("erreur input\n"), 1);
	table = malloc(sizeof(t_table));
	if(!table)
		return (0);
	init_struct(table, av);
	int	i; 
	
	i = 0;
	while (i < table->nb_philo)
	{
		// printf("FOR I = %d, LEFT FORK = %d, RIGHT FORK = %d\n", i, table->philo[i].left_fork, table->philo[i].right_fork);
		pthread_create(&table->philo[i].thread, NULL, &philo_routine, &table->philo[i]);
		// printf("THREAD CREATED = %lu\n", table->philo[i].thread);
		usleep(500);
		i++;
	}
	i = 0;
	while(i < table->nb_philo)
	{
		pthread_join(table->philo[i].thread, NULL);
		// printf("THREAD WAITING = %lu\n", table->philo[i].thread);
		i++;
		
	}
	int j = 0;
	while (j < table->nb_philo)
	{
		pthread_mutex_destroy(table->forks[j]);
		j++;
	}
	free(table->philo);
	free(table);
	return (0);
}

// void	*check_philo_death(void *arg)
// {
// 	t_table	*table;
	
// 	table = (t_table *)
// }