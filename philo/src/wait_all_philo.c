/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_all_philo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:38:11 by seb               #+#    #+#             */
/*   Updated: 2025/05/31 16:56:23 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	wait_for_all_philosophers(t_global_info *infos)
{
	int	i;

	i = 0;
	while (i < infos->nbr_of_philosophers)
	{
		pthread_join(infos->table_of_philo[i].id_thread, NULL);
		i++;
	}
}
