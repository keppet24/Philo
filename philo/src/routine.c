/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:40:54 by seb               #+#    #+#             */
/*   Updated: 2025/05/31 16:56:14 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	routine_even(t_philo *philo)
{
	if (!simulation_is_not_ended(philo))
		return (0);
	printf_mutex_thinking(philo);
	take_two_fork_even(philo);
	if (!simulation_is_not_ended(philo))
	{
		drop_the_forks_even(philo);
		return (0);
	}
	eating_process(philo);
	drop_the_forks_even(philo);
	if (!simulation_is_not_ended(philo))
		return (0);
	printf_mutex_sleeping(philo);
	return (1);
}

static int	routine_odd(t_philo *philo)
{
	usleep(500);
	if (!simulation_is_not_ended(philo))
		return (0);
	printf_mutex_thinking(philo);
	take_two_forks_odd(philo);
	if (!simulation_is_not_ended(philo))
	{
		drop_the_forks_odd(philo);
		return (0);
	}
	eating_process(philo);
	drop_the_forks_odd(philo);
	if (!simulation_is_not_ended(philo))
		return (0);
	printf_mutex_sleeping(philo);
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (simulation_is_not_ended(philo))
	{
		if (philo->id % 2 == 0)
		{
			if (!routine_even(philo))
				return (NULL);
		}
		else
		{
			if (!routine_odd(philo))
				return (NULL);
		}
	}
	return (NULL);
}
