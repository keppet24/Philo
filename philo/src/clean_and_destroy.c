/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_and_destroy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:36:58 by seb               #+#    #+#             */
/*   Updated: 2025/05/31 16:58:56 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	clean_and_destroy(t_global_info *infos)
{
	int	i;

	i = 0;
	while (i < infos->nbr_of_philosophers)
	{
		pthread_mutex_destroy(&infos->table_of_philo[i].mutex_info_meal_philo);
		pthread_mutex_destroy(&infos->table_of_fork[i].mutex_of_the_fork);
		i++;
	}
	free(infos->table_of_philo);
	free(infos->table_of_fork);
	pthread_mutex_destroy(&infos->mutex_on_write);
	pthread_mutex_destroy(&infos->mutex_info_die_of_philo);
	free(infos);
}
