/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:34:21 by seb               #+#    #+#             */
/*   Updated: 2025/05/31 17:05:46 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*routine_one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf_mutex_thinking(philo);
	return (NULL);
}

static void	init_if_one_philo(t_global_info *infos)
{
	pthread_t	id_monitor_thread;

	infos->table_of_fork[0].id = 0;
	pthread_mutex_init(&(infos->table_of_fork[0].mutex_of_the_fork), NULL);
	infos->table_of_philo[0].id = 0;
	infos->table_of_philo[0].left_fork = &infos->table_of_fork[0];
	infos->table_of_philo[0].right_fork = &infos->table_of_fork[0];
	infos->table_of_philo[0].last_eating_time = infos->beginning_of_simulation;
	infos->table_of_philo[0].numbers_of_meal_eaten = 0;
	infos->table_of_philo[0].infos = infos;
	pthread_mutex_init(&infos->table_of_philo[0].mutex_info_meal_philo, NULL);
	pthread_mutex_init(&infos->mutex_on_write, NULL);
	pthread_mutex_init(&infos->mutex_info_die_of_philo, NULL);
	pthread_create(&(infos->table_of_philo[0].id_thread),
		NULL, routine_one_philo, &(infos->table_of_philo[0]));
	pthread_create(&id_monitor_thread, NULL, monitor, infos);
	pthread_join(id_monitor_thread, NULL);
	pthread_join(infos->table_of_philo[0].id_thread, NULL);
	pthread_mutex_destroy(&infos->table_of_philo[0].mutex_info_meal_philo);
	pthread_mutex_destroy(&infos->table_of_fork[0].mutex_of_the_fork);
	pthread_mutex_destroy(&infos->mutex_on_write);
}

int	one_philo_case(t_global_info *infos)
{
	infos->beginning_of_simulation = timetamp();
	infos->table_of_philo = malloc(sizeof(t_philo));
	if (!infos->table_of_philo)
	{
		free(infos);
		return (0);
	}
	infos->table_of_fork = malloc(sizeof(t_fork));
	if (!infos->table_of_fork)
	{
		free(infos->table_of_philo);
		free(infos);
		return (0);
	}
	init_if_one_philo(infos);
	free(infos->table_of_philo);
	free(infos->table_of_fork);
	free(infos);
	return (1);
}
