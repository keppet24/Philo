/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oettaqi <oettaqi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:10:19 by othmaneetta       #+#    #+#             */
/*   Updated: 2025/06/01 21:46:17 by oettaqi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_atoi(char *s1)
{
	int	i;
	int	signe;
	int	resu;

	i = 0;
	resu = 0;
	signe = 1;
	while (s1[i] == 32 || (s1[i] >= 9 && s1[i] <= 13))
		i++;
	if (s1[i] == '+')
		i++;
	else if (s1[i] == '-')
	{
		signe = -1;
		i++;
	}
	while (s1[i] >= 48 && s1[i] <= 57)
	{
		resu = resu * 10 + (s1[i] - 48);
		i++;
	}
	return (signe * resu);
}

static int	is_all_digits(char *str)
{
	if (!str || *str == '\0')
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

static int	parse_error(const char *msg, size_t len)
{
	write(2, msg, len);
	return (0);
}

static int	validate_argument(char *arg, int idx)
{
	int	val;

	if (!is_all_digits(arg))
		return (parse_error(
				"Error: Arguments must contain only digits.\n", 43));
	val = ft_atoi(arg);
	if (idx != 5 && val <= 0)
		return (parse_error(
				"Error: Arguments 1-4 must be strictly positive.\n", 49));
	if (idx == 5 && val < 0)
		return (parse_error(
				"Error: Optional argument must be non-negative.\n", 48));
	return (1);
}

int	parsing(int ac, char **av)
{
	int	i;

	if (ac < 5 || ac > 6)
		return (parse_error("Error: Invalid number of arguments.\n", 36));
	i = 1;
	while (i < ac)
	{
		if (!validate_argument(av[i], i))
			return (0);
		i++;
	}
	if (ac == 6 && ft_atoi(av[5]) == 0)
	{
		printf("number_of_times_each_philosopher_must_eat");
		printf(" should be at least 1.\n");
		return (0);
	}
	return (1);
}

// int	parsing(int ac, char **av)
// {
// 	int	value;
// 	int	i;

// 	if (ac < 5 || ac > 6)
// 	{
// 		write(2, "Error: Invalid number of arguments.\n", 36);
// 		return (0);
// 	}
// 	i = 1;
// 	while (i < ac)
// 	{
// 		if (!is_all_digits(av[i]))
// 		{
// 			write(2, "Error: Arguments must contain only digits.\n", 43);
// 			return (0);
// 		}
// 		value = ft_atoi(av[i]);
// 		if (value <= 0 && i != 5)
// 		{
// 			write(2, "Error: Arguments 1-4 must be strictly positive.\n", 49);
// 			return (0);
// 		}
// 		if (value < 0 && i == 5)
// 		{
// 			write(2, "Error: Optional argument must be non-negative.\n", 48);
// 			return (0);
// 		}
// 		i++;
// 	}
// 	if (ac == 6 && ft_atoi(av[5]) == 0)
// 	{
// 		printf("number_of_times_each_philosopher_must_eat");
// 		printf(" should be at least 1. \n");
// 		return (0);
// 	}
// 	return (1);
// }
