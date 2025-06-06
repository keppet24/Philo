/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oettaqi <oettaqi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:35:55 by seb               #+#    #+#             */
/*   Updated: 2025/06/01 21:37:20 by oettaqi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// void	*monitor(void *arg)
// {
// 	t_global_info	*infos;
// 	long			current_time;
// 	int				i;

// 	infos = (t_global_info *)arg;
// 	while (1)
// 	{
// 		pthread_mutex_lock(&infos->mutex_finished);
// 		if (infos->nbr_of_time_each_philo_must_eat != -1
// 			&& infos->philos_finished == infos->nbr_of_philosophers)
// 		{
// 			pthread_mutex_unlock(&infos->mutex_finished);
// 			pthread_mutex_lock(&infos->mutex_info_die_of_philo);
// 			infos->a_philo_has_died = 1;
// 			pthread_mutex_unlock(&infos->mutex_info_die_of_philo);
// 			return (NULL);
// 		}
// 		pthread_mutex_unlock(&infos->mutex_finished);
// 		i = 0;
// 		while (i < infos->nbr_of_philosophers)
// 		{
// 			current_time = timetamp();
// 			pthread_mutex_lock(&infos->table_of_philo[i].mutex_info_meal_philo);
// 			if (current_time - infos->table_of_philo[i].last_eating_time
// 				> infos->time_to_die)
// 			{
// 				a_philo_died(infos, i);
// 				return (NULL);
// 			}
// 			pthread_mutex_unlock
// 				(&infos->table_of_philo[i].mutex_info_meal_philo);
// 			i++;
// 		}
// 		usleep(1000);
// 	}
// }

/*------------------------------------------------------------*/
/*  Auxiliaire : renvoie 1 si un philosophe vient de mourir   */
/*------------------------------------------------------------*/
static int	check_philo_death(t_global_info *infos)
{
	int		i;
	long	now;

	i = 0;
	while (i < infos->nbr_of_philosophers)
	{
		now = timetamp();
		pthread_mutex_lock(&infos->table_of_philo[i].mutex_info_meal_philo);
		if (now - infos->table_of_philo[i].last_eating_time
			> infos->time_to_die)
		{
			a_philo_died(infos, i);
			return (1);
		}
		pthread_mutex_unlock(&infos->table_of_philo[i].mutex_info_meal_philo);
		i++;
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_global_info	*infos;

	infos = (t_global_info *)arg;
	while (1)
	{
		pthread_mutex_lock(&infos->mutex_finished);
		if (infos->nbr_of_time_each_philo_must_eat != -1
			&& infos->philos_finished == infos->nbr_of_philosophers)
		{
			pthread_mutex_unlock(&infos->mutex_finished);
			pthread_mutex_lock(&infos->mutex_info_die_of_philo);
			infos->a_philo_has_died = 1;
			pthread_mutex_unlock(&infos->mutex_info_die_of_philo);
			return (NULL);
		}
		pthread_mutex_unlock(&infos->mutex_finished);
		if (check_philo_death(infos))
			return (NULL);
		usleep(1000);
	}
}
