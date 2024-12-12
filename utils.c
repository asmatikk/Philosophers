/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:06:11 by afrikach          #+#    #+#             */
/*   Updated: 2024/12/12 12:59:24 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	nb;
	int	i;
	int	sign;

	nb = 0;
	i = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = sign * (-1);
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (nb > INT_MAX)
		return (-1);
	return (nb * sign);
}

long int	timestamp(void)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_routine(t_philo *philo, char c)
{
	long int	time;
	int			philo_id;

	time = timestamp() - philo->table->start_routine;
	philo_id = philo->id;
	if (c == 'f')
		printf("%s%ld %d has taken a fork%s\n", BWHITE, time, philo_id + 1, RESET);
	if (c == 'e')
	{
		printf("%s%ld %d is eating%s\n", BGREEN, time, philo_id + 1, RESET);
		usleep(philo->table->t_to_eat);
		philo->last_meal = timestamp();
	}
	if (c == 's')
	{
		printf("%s%ld %d is sleeping%s\n", BCYAN, time, philo_id + 1, RESET);
		usleep(philo->table->t_to_sleep);
	}
	if (c == 't')
		printf("%s%ld %d is thinking%s\n", BMAG, time, philo_id + 1, RESET);
	if (c == 'd')
		printf("%s%ld %d is died%s\n", BRED, time, philo_id + 1, RESET);
		
}
