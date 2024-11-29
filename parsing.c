/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:26:47 by afrikach          #+#    #+#             */
/*   Updated: 2024/11/29 17:40:47 by afrikach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//check if only digits

int	check_digit(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_input(int ac, char **av)
{
	int	i;
	int	nb;
	
	i = 1;
	while(i < ac)
	{
		if (!check_digit(av[i]))
			return (1);
		if (ac > 5 || ac < 5)
			return (1);
		nb = ft_atoi(av[i]);
		if (i != 1 && nb == -1)
			return (1);
		i++;
	}
	return (0);
}
// int	convert_argu(char *str)
// {
// 	int i;
// 	long long int nb;

// 	i = 0;
// 	nb = 0;
// 	if (nb > INT_MAX)
// 		return (-1);
// 	while(str[i])
// 	{
// 		while (str[i] >= '0' && str[i] <= '9')
// 		{
// 			nb = nb * 10 + (str[i] - '0');
// 			i++;
// 		}
// 	}
// 	return ((int)nb);
// }