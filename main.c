/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:26:51 by afrikach          #+#    #+#             */
/*   Updated: 2024/12/06 17:29:56 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philo_routine(void *arg)
{
    t_philo *philo;
	// t_table	*table;
	int left_fork;
	int right_fork;
	int i;

	i = 0;	
	philo = (t_philo *)arg;
	while(1)
	{
		printf("PHILO == %d\n", i);
		left_fork = philo[i].id;
		right_fork = (philo[i].id + 1) % philo->table->nb_philo;

		pthread_mutex_lock(&philo->table->forks[left_fork]);
		pthread_mutex_lock(&philo->table->forks[right_fork]);
		printf("philo n%d is eating\n", philo[i].id);
		
		pthread_mutex_unlock(&philo->table->forks[left_fork]);
		pthread_mutex_unlock(&philo->table->forks[right_fork]);

		}
		i++;
	}
    printf("Philosopher %d is eating with forks %d and %d.\n", 
           philo->id, philo->left_fork, philo->right_fork);
    return (NULL);
}

int	main(int ac, char **av)
{
	t_table *table = NULL;
	
	if (check_input(ac, av) == 1)
	{
		// free(table);
		return (printf("erreur input\n"), 1);
	}
	table = malloc(sizeof(t_table));
	if(!table)
		return (0);
	init_struct(table, av);
	printf("NB PHILO == %d\n", table->nb_philo);
	printf("time to die == %d", table->t_to_die);

	int	i; 
	
	i = 0;
	while (i < table->nb_philo)
	{
		pthread_create(&table->philo[i].thread, NULL, &philo_routine, &table->philo[i]);
		usleep(2000);
		printf("I == %d\n", i);
		i++;
	}
	i = 0;
	while(i < table->nb_philo)
	{
		pthread_join(table->philo[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
	}
	free(table);
	return (0);
}
