/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oettaqi <oettaqi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:44:13 by seb               #+#    #+#             */
/*   Updated: 2025/06/01 21:02:22 by oettaqi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	eating_process(t_philo *p)
{
	int	meals;

	pthread_mutex_lock(&p->mutex_info_meal_philo);
	p->numbers_of_meal_eaten++;
	p->last_eating_time = timetamp();
	meals = p->numbers_of_meal_eaten;
	pthread_mutex_unlock(&p->mutex_info_meal_philo);
	if (p->infos->nbr_of_time_each_philo_must_eat != -1
		&& meals == p->infos->nbr_of_time_each_philo_must_eat)
	{
		pthread_mutex_lock(&p->infos->mutex_finished);
		p->infos->philos_finished++;
		pthread_mutex_unlock(&p->infos->mutex_finished);
	}
	pthread_mutex_lock(&p->infos->mutex_on_write);
	printf("%ld %d has taken a fork\n",
		timetamp() - p->infos->beginning_of_simulation, p->id + 1);
	printf("%ld %d has taken a fork\n",
		timetamp() - p->infos->beginning_of_simulation, p->id + 1);
	printf("%ld %d is eating\n",
		timetamp() - p->infos->beginning_of_simulation, p->id + 1);
	pthread_mutex_unlock(&p->infos->mutex_on_write);
	precise_sleep(p->infos->time_to_eat);
}
