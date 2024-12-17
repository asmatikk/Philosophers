/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:26:51 by afrikach          #+#    #+#             */
/*   Updated: 2024/12/13 17:30:21 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philo_routine(void *arg)
{
    t_philo *philo;
	t_table *table;
		
	philo = (t_philo *)arg;
	table = philo->table;
	if (philo_alone(philo) == 1)
		return (NULL);
	while(1)
	{
		// if (check_philos_death(philo) == 1)
		// 	break ;
		// if (table->nb_death >= 1)
		// 	break ;
		philo_eat(philo, table);
		if (table->times_must_eat != -1 && table->times_must_eat == philo->nb_meals)
			break ;
		if (check_philos_death(philo) == 1)
			break ;
		print_routine(philo, 's');
		if (check_philos_death(philo) == 1)
			break ;
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
	init_struct_table(table, ac, av);
	i = 0;
	while (i < table->nb_philo)
	{
		pthread_create(&table->philo[i].thread, NULL, &philo_routine, &table->philo[i]);
		usleep(200);
		i++;
	}
	i = 0;
	while(i < table->nb_philo)
		pthread_join(table->philo[i++].thread, NULL);
	i = 0;
	while (i < table->nb_philo)
		pthread_mutex_destroy(&table->forks[i++]);
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->death);
	free(table->forks);
	free(table->philo);
	free(table);
	return (0);
}

int	check_philos_death(t_philo	*philo)
{
	long int	current;
	
	pthread_mutex_lock(&philo->table->death);
	current = timestamp();
	if (philo->table->nb_death >= 1)
	{
		pthread_mutex_unlock(&philo->table->death);
			return (1);
	}
	if ((philo->last_meal + philo->table->t_to_die / 1000) < (current + philo->table->t_to_eat / 1000))
	{
		if (philo->table->nb_death == 0)
			print_routine(philo, 'd');
		philo->table->nb_death++;
		pthread_mutex_unlock(&philo->table->death);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->death);
	return (0);
}

