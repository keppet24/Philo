/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oettaqi <oettaqi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:45:28 by seb               #+#    #+#             */
/*   Updated: 2025/06/01 21:06:09 by oettaqi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	printf_mutex_sleeping(t_philo *p)
{
	pthread_mutex_lock(&p->infos->mutex_on_write);
	printf("%ld %d is sleeping\n",
		timetamp() - p->infos->beginning_of_simulation, p->id + 1);
	pthread_mutex_unlock(&p->infos->mutex_on_write);
	precise_sleep(p->infos->time_to_sleep);
}

void	printf_mutex_thinking(t_philo *philo)
{
	long	delta;

	delta = timetamp() - philo->infos->beginning_of_simulation;
	pthread_mutex_lock(&philo->infos->mutex_on_write);
	printf("%ld %d is thinking\n", delta, philo->id + 1);
	pthread_mutex_unlock(&philo->infos->mutex_on_write);
}
