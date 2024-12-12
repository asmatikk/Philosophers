/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:26:51 by afrikach          #+#    #+#             */
/*   Updated: 2024/12/12 14:55:14 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philo_routine(void *arg)
{
    t_philo *philo;
	t_table *table;
		
	philo = (t_philo *)arg;
	table = philo->table;

	if (philo->id % 2 != 0)
		usleep(table->t_to_eat);
	print_routine(philo, 't');
	while(1)
	{
			pthread_mutex_lock(table->forks[philo->left_fork]);
			print_routine(philo, 'f');
			pthread_mutex_lock(table->forks[philo->right_fork]);
			print_routine(philo, 'f');
			print_routine(philo, 'e');
			philo->last_meal = timestamp();
			printf("philo n%d needs %ld time to eat\n", philo->id, philo->last_meal - table->start_routine);
			pthread_mutex_unlock(table->forks[philo->left_fork]);
			pthread_mutex_unlock(table->forks[philo->right_fork]);
			print_routine(philo, 's');
			print_routine(philo, 't');
	}
    return (NULL);
}

int	main(int ac, char **av)
{
	t_table *table = NULL;
	int	i; 
	
	if (check_input(ac, av) == 1)
		return (printf("erreur input\n"), 1);
	table = malloc(sizeof(t_table));
	if(!table)
		return (0);
	init_struct(table, av);
	i = 0;
	while (i < table->nb_philo)
	{
		pthread_create(&table->philo[i].thread, NULL, &philo_routine, &table->philo[i]);
		i++;
	}
	i = 0;
	while(i < table->nb_philo)
		pthread_join(table->philo[i++].thread, NULL);
	int j = 0;
	while (j < table->nb_philo)
		pthread_mutex_destroy(table->forks[j++]);
	free(table->philo);
	free(table);
	return (0);
}

// void	*check_philo_death(void *arg)
// {
// 	t_table	*table;
	
// 	table = (t_table *)
// }

// Regarder pour chacun la dernier fois qu'ils ont manger et faire last_meal - t_to_death.
// si = a 0 alors philo doit mourir et on break.
// trouver un moyen de verifier si les philos ne sont pas morts pendant chaque Usleep.


