/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oettaqi <oettaqi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:40:21 by seb               #+#    #+#             */
/*   Updated: 2025/06/01 21:55:47 by oettaqi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	malloc_infos(t_global_info *infos)
{
	infos->beginning_of_simulation = timetamp();
	infos->table_of_philo
		= malloc(sizeof(t_philo) * infos->nbr_of_philosophers);
	if (!infos->table_of_philo)
	{
		free(infos->table_of_philo);
		free(infos);
		return (0);
	}
	infos->table_of_fork = malloc(sizeof(t_fork) * infos->nbr_of_philosophers);
	if (!infos->table_of_fork)
	{
		free(infos);
		return (0);
	}
	return (1);
}

void	philo_init(t_global_info *infos, int i)
{
	infos->table_of_fork[i].id = i;
	pthread_mutex_init(&(infos->table_of_fork[i].mutex_of_the_fork), NULL);
	infos->table_of_philo[i].id = i;
	infos->table_of_philo[i].left_fork = &infos->table_of_fork[i];
	infos->table_of_philo[i].right_fork
		= &infos->table_of_fork[(i + 1) % infos->nbr_of_philosophers];
	infos->table_of_philo[i].last_eating_time = infos->beginning_of_simulation;
	infos->table_of_philo[i].numbers_of_meal_eaten = 0;
	infos->table_of_philo[i].infos = infos;
	pthread_mutex_init(&infos->table_of_philo[i].mutex_info_meal_philo, NULL);
}

void	create_philo_and_set_the_table(t_global_info *infos)
{
	int	i;

	i = 0;
	if (malloc_infos(infos) == 0)
		return ;
	while (i < infos->nbr_of_philosophers)
		philo_init(infos, i++);
	i = 0;
	while (i < infos->nbr_of_philosophers)
	{	
		if (pthread_create(&(infos->table_of_philo[i].id_thread),
				NULL, routine, &(infos->table_of_philo[i])))
			break ;
		i++;
	}
}
