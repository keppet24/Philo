/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_is_not_ended.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:49:30 by seb               #+#    #+#             */
/*   Updated: 2025/05/31 16:56:17 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	simulation_is_not_ended(t_philo *philo)
{
	int	resu;

	resu = 0;
	pthread_mutex_lock(&philo->infos->mutex_info_die_of_philo);
	if (philo->infos->a_philo_has_died == 1)
		resu = 0;
	else
		resu = 1;
	pthread_mutex_unlock(&philo->infos->mutex_info_die_of_philo);
	return (resu);
}
