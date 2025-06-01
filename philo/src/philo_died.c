/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_died.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oettaqi <oettaqi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:37:33 by seb               #+#    #+#             */
/*   Updated: 2025/06/01 21:02:56 by oettaqi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	a_philo_died(t_global_info *infos, int i)
{
	pthread_mutex_lock(&infos->mutex_info_die_of_philo);
	infos->a_philo_has_died = 1;
	pthread_mutex_unlock(&infos->mutex_info_die_of_philo);
	pthread_mutex_lock(&infos->mutex_on_write);
	printf("%ld %d died \n", timetamp() - infos->beginning_of_simulation,
		infos->table_of_philo[i].id + 1);
	pthread_mutex_unlock(&infos->mutex_on_write);
	pthread_mutex_unlock(&infos->table_of_philo[i].mutex_info_meal_philo);
}
