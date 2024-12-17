/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:04:26 by afrikach          #+#    #+#             */
/*   Updated: 2024/12/13 17:29:21 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int	philo_alone(t_philo *philo)
{
	if (philo->table->nb_philo == 1)
	{
		usleep(philo->table->t_to_die);
		print_routine(philo, 'd');
		return(1);
	}
	// if (table->philo->id % 2 != 0)
		// usleep(table->t_to_eat);
	print_routine(philo, 't');
	return (0);
}

void	philo_eat(t_philo *philo, t_table *table)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(&table->forks[philo->left_fork]);
		if (table->nb_death >= 1)
		{
			pthread_mutex_unlock(&table->forks[philo->left_fork]);
			return ;
		}
		print_routine(philo, 'f');
		pthread_mutex_lock(&table->forks[philo->right_fork]);
		check_philos_death(philo);
		if (table->nb_death >= 1)
		{
			pthread_mutex_unlock(&table->forks[philo->right_fork]);
			pthread_mutex_unlock(&table->forks[philo->left_fork]);
			return ;
		}
		print_routine(philo, 'f');
		check_philos_death(philo);
		if (table->nb_death >= 1)
		{
			pthread_mutex_unlock(&table->forks[philo->right_fork]);
			pthread_mutex_unlock(&table->forks[philo->left_fork]);
			return ;
		}
		print_routine(philo, 'e');
		philo->nb_meals++;
		pthread_mutex_unlock(&table->forks[philo->right_fork]);
		pthread_mutex_unlock(&table->forks[philo->left_fork]);
	}
	else
	{
		pthread_mutex_lock(&table->forks[philo->right_fork]);
		if (table->nb_death >= 1)
		{
			pthread_mutex_unlock(&table->forks[philo->right_fork]);
			return ;
		}
		print_routine(philo, 'f');
		check_philos_death(philo);
		pthread_mutex_lock(&table->forks[philo->left_fork]);
		if (table->nb_death >= 1)
		{
			pthread_mutex_unlock(&table->forks[philo->left_fork]);
			pthread_mutex_unlock(&table->forks[philo->right_fork]);
			return ;
		}
		print_routine(philo, 'f');
		check_philos_death(philo);
		if (table->nb_death >= 1)
		{
			pthread_mutex_unlock(&table->forks[philo->left_fork]);
			pthread_mutex_unlock(&table->forks[philo->right_fork]);
			return ;
		}
		print_routine(philo, 'e');
		philo->nb_meals++;
		pthread_mutex_unlock(&table->forks[philo->left_fork]);
		pthread_mutex_unlock(&table->forks[philo->right_fork]);
	}
	
}

void	print_routine(t_philo *philo, char c)
{
	long int	time;

	time = timestamp() - philo->table->start_routine;
	pthread_mutex_lock(&philo->table->print);
	if (c == 'f')
	{
		printf("%s%ld %d has taken a fork%s\n", BWHITE, time, philo->id + 1, RESET);
		pthread_mutex_unlock(&philo->table->print);
	}
	if (c == 'e')
	{
		printf("%s%ld %d is eating%s\n", BGREEN, time, philo->id + 1, RESET);
		pthread_mutex_unlock(&philo->table->print);
		usleep(philo->table->t_to_eat);
		philo->last_meal = timestamp();
	}
	if (c == 's')
	{
		printf("%s%ld %d is sleeping%s\n", BCYAN, time, philo->id + 1, RESET);
		pthread_mutex_unlock(&philo->table->print);
		usleep(philo->table->t_to_sleep);
	}
	if (c == 't')
	{
		printf("%s%ld %d is thinking%s\n", BMAG, time, philo->id + 1, RESET);
		pthread_mutex_unlock(&philo->table->print);
	}
	if (c == 'd')
	{
		printf("%s%ld %d died%s\n", BRED, time, philo->id + 1, RESET);
		pthread_mutex_unlock(&philo->table->print);
	}
}

