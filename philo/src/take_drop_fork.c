/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_drop_fork.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:44:51 by seb               #+#    #+#             */
/*   Updated: 2025/05/31 16:56:20 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	take_two_forks_odd(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->mutex_of_the_fork);
	pthread_mutex_lock(&philo->left_fork->mutex_of_the_fork);
}

void	take_two_fork_even(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex_of_the_fork);
	pthread_mutex_lock(&philo->right_fork->mutex_of_the_fork);
}

void	drop_the_forks_odd(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork->mutex_of_the_fork);
	pthread_mutex_unlock(&philo->right_fork->mutex_of_the_fork);
}

void	drop_the_forks_even(t_philo *philo)
{
	pthread_mutex_unlock(&philo->right_fork->mutex_of_the_fork);
	pthread_mutex_unlock(&philo->left_fork->mutex_of_the_fork);
}
