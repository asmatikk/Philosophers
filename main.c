/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:26:51 by afrikach          #+#    #+#             */
/*   Updated: 2024/12/10 12:27:30 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philo_routine(void *arg)
{
    t_philo *philo;
	t_table *table = NULL;
	int	i = 0;	
	
	philo = (t_philo *)arg;
	while(i < table->nb_philo)
	{
		printf("id = %d\n",table->philo[i].id);
		printf("left_fork = %d\n", table->philo[i].left_fork);
		printf("right_fork = %d\n", table->philo[i].right_fork);
		pthread_mutex_lock(&table->forks[philo[i].left_fork]);
		pthread_mutex_lock(&table->forks[philo[i].right_fork]);
		printf("philo n%d is eating\n", table->philo[i].id);

        usleep(philo->table->t_to_eat);
		pthread_mutex_unlock(&table->forks[philo[i].left_fork]);
		pthread_mutex_unlock(&table->forks[philo[i].right_fork]);
		// Philosophe dort
        // printf("Philosopher %d is sleeping\n", philo->id);
        // usleep(philo->table->t_to_sleep);

        // Philosophe pense
        // printf("Philosopher %d is thinking\n", philo->id);
	}
    // printf("Philosopher %d is eating with forks %d and %d.\n", 
    //        philo->id, philo->left_fork, philo->right_fork);
    return (NULL);
}

// void	*check_philo_death(void *arg)
// {
// 	t_table	*table;
	
// 	table = (t_table *)
// }

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
	printf("NB PHILO %d\n", table->nb_philo);
	while (i < table->nb_philo)
	{
		printf("I == %d\n", i);
		printf("LEFT FORK %d\n", table->philo[i].left_fork);
		printf("RIGHT FORK %d\n", table->philo[i].right_fork);
		printf("TIME TO SLEEP %d\n", table->t_to_sleep);
		printf("TIME TO EAT %d\n", table->t_to_eat);
		printf("TIME TO DIE %d\n", table->t_to_die);
		pthread_create(&table->philo[i].thread, NULL, &philo_routine, &table->philo[i]);
		i++;
	}
	i = 0;
	while(i < table->nb_philo)
	{
		pthread_join(table->philo[i].thread, NULL);
		i++;
	}
	int j = 0;
	while (j < table->nb_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
	}
	free(table);
	return (0);
}
