/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othmaneettaqi <othmaneettaqi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:55:45 by othmaneetta       #+#    #+#             */
/*   Updated: 2025/05/27 22:26:15 by othmaneetta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		simulation_is_not_ended(t_philo *philo)
{
	pthread_mutex_lock(&philo->infos->mutex_info_die_of_philo);
	if (philo->infos->a_philo_has_died == 1)
	{
		pthread_mutex_unlock(&philo->infos->mutex_info_die_of_philo);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&philo->infos->mutex_info_die_of_philo);
		return (1);
	}
	
}

void	*routine(void *arg)
{
	t_philo	*philo;
	struct timeval time;
	long	seconds;
	long	microseconds;
	long	current_time;

	philo = (t_philo *)arg;
	while (simulation_is_not_ended(philo))
	{
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(&philo->infos->mutex_on_write);
			printf("je reflechis \n");
			pthread_mutex_unlock(&philo->infos->mutex_on_write);
			
			pthread_mutex_lock(&philo->left_fork->mutex_of_the_fork);
			pthread_mutex_lock(&philo->infos->mutex_on_write);
			printf("j ai pris une fourchette \n");
			pthread_mutex_unlock(&philo->infos->mutex_on_write);
			
			pthread_mutex_lock(&philo->right_fork->mutex_of_the_fork);
				
			pthread_mutex_lock(&philo->infos->mutex_on_write);
			printf("j ai pris une fourchette \n");
			pthread_mutex_unlock(&philo->infos->mutex_on_write);
			gettimeofday(&time, NULL);
			seconds = time.tv_sec;
			microseconds = time.tv_usec;
			current_time = (seconds * 1000) + (microseconds / 1000);
			
			pthread_mutex_lock(&philo->mutex_info_meal_philo);
			philo->last_eating_time = current_time;
			philo->numbers_of_meal_eaten++;
			pthread_mutex_unlock(&philo->mutex_info_meal_philo);
			pthread_mutex_lock(&philo->infos->mutex_on_write);
			printf("je mange \n");
			pthread_mutex_unlock(&philo->infos->mutex_on_write);
			usleep(philo->infos->time_to_eat * 1000);
			
			
			

			pthread_mutex_unlock(&philo->left_fork->mutex_of_the_fork);
			pthread_mutex_unlock(&philo->right_fork->mutex_of_the_fork);
			
			pthread_mutex_lock(&philo->infos->mutex_on_write);
			printf("je dors \n");
			usleep(philo->infos->time_to_sleep * 1000);
			pthread_mutex_unlock(&philo->infos->mutex_on_write);	
		}
		else
		{		
			pthread_mutex_lock(&philo->infos->mutex_on_write);
			printf("je reflechis \n");
			pthread_mutex_unlock(&philo->infos->mutex_on_write);
		
			pthread_mutex_lock(&philo->right_fork->mutex_of_the_fork);
			pthread_mutex_lock(&philo->infos->mutex_on_write);
			printf("j ai pris une fourchette \n");
			pthread_mutex_unlock(&philo->infos->mutex_on_write);
		
			pthread_mutex_lock(&philo->left_fork->mutex_of_the_fork);
			pthread_mutex_lock(&philo->infos->mutex_on_write);
			printf("j ai pris une fourchette \n");
			pthread_mutex_unlock(&philo->infos->mutex_on_write);
		
			gettimeofday(&time, NULL);
			seconds = time.tv_sec;
			microseconds = time.tv_usec;
			current_time = (seconds * 1000) + (microseconds / 1000);
		
			pthread_mutex_lock(&philo->mutex_info_meal_philo);
			philo->last_eating_time = current_time;
			philo->numbers_of_meal_eaten++;
			pthread_mutex_unlock(&philo->mutex_info_meal_philo);
		
			pthread_mutex_lock(&philo->infos->mutex_on_write);
			printf("je mange \n");
			pthread_mutex_unlock(&philo->infos->mutex_on_write);
		
			usleep(philo->infos->time_to_eat * 1000);
		
			pthread_mutex_unlock(&philo->right_fork->mutex_of_the_fork);
			pthread_mutex_unlock(&philo->left_fork->mutex_of_the_fork);
		
			pthread_mutex_lock(&philo->infos->mutex_on_write);
			printf("je dors \n");
			usleep(philo->infos->time_to_sleep * 1000);
			pthread_mutex_unlock(&philo->infos->mutex_on_write);
		}	
	}
	return NULL;
}

void	create_philo_and_set_the_table(t_global_info *infos)
{
	struct timeval time;
	int	i;
	long	beginning_of_simulation;
	long	seconds;
	long	microseconds;

	gettimeofday(&time, NULL);
	seconds = time.tv_sec;
	microseconds = time.tv_usec;
	beginning_of_simulation = (seconds * 1000) + (microseconds / 1000);
	i = 0;
	infos->table_of_fork = malloc(sizeof(t_fork ) * infos->nbr_of_philosophers);
	if (!infos->table_of_fork)
		return ; //(faudrait  free)
	infos->table_of_philo = malloc(sizeof(t_philo ) * infos->nbr_of_philosophers);
	if (!infos->table_of_philo)
		return ; //(faudrait  free)
	while (i < infos->nbr_of_philosophers)
	{
		infos->table_of_fork[i].id = i;
		pthread_mutex_init(&(infos->table_of_fork[i].mutex_of_the_fork), NULL);
		infos->table_of_philo[i].id = i;
		infos->table_of_philo[i].left_fork = &infos->table_of_fork[i];
		infos->table_of_philo[i].right_fork = &infos->table_of_fork[(i + 1) % infos->nbr_of_philosophers];
		infos->table_of_philo[i].last_eating_time = beginning_of_simulation;
		infos->table_of_philo[i].numbers_of_meal_eaten = 0;
		infos->table_of_philo[i].infos = infos;
		pthread_mutex_init(&infos->table_of_philo[i].mutex_info_meal_philo, NULL);
		pthread_create(&(infos->table_of_philo[i].id_thread), NULL, routine, &(infos->table_of_philo[i]));
		i++;
	}
}

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

void	*monitor(void *arg)
{
	int i;
	long	seconds;
	long	microseconds;
	long	current_time;
	struct timeval time;
	t_global_info *infos;

	infos = (t_global_info *)arg;
	i = 0;
	while (1)
	{
		i = 0;
		while (i < infos->nbr_of_philosophers)
		{
			gettimeofday(&time, NULL);
			seconds = time.tv_sec;
			microseconds = time.tv_usec;
			current_time = (seconds * 1000) + (microseconds / 1000);
			pthread_mutex_lock(&infos->table_of_philo[i].mutex_info_meal_philo);
			if (current_time - infos->table_of_philo[i].last_eating_time > infos->time_to_die)
			{
				pthread_mutex_lock(&infos->mutex_info_die_of_philo);
				infos->a_philo_has_died = 1;
				pthread_mutex_unlock(&infos->mutex_info_die_of_philo);
				pthread_mutex_lock(&infos->mutex_on_write);
				printf("un philo est mort \n");
				pthread_mutex_unlock(&infos->mutex_on_write);
				pthread_mutex_unlock(&infos->table_of_philo[i].mutex_info_meal_philo);
				return  NULL;
			}
			pthread_mutex_unlock(&infos->table_of_philo[i].mutex_info_meal_philo);
			i++;
		}
		usleep(1000);
	}
}

int main(int ac, char **av)
{
	(void)ac;
	t_global_info	*infos;
	pthread_t id_monitor;
	// if (parsing(ac, av) == 0)
	// 	return (write("ERROR"));
	infos = malloc(sizeof(t_global_info));
	infos->nbr_of_philosophers = atoi(av[1]);
	infos->time_to_die = atoi(av[2]);
	infos->time_to_eat = atoi(av[3]);
	infos->time_to_sleep = atoi(av[4]);
	infos->a_philo_has_died = 0;
	pthread_mutex_init(&infos->mutex_info_die_of_philo, NULL);
	pthread_mutex_init(&infos->mutex_on_write, NULL);
	create_philo_and_set_the_table(infos);
	pthread_create(&id_monitor, NULL, monitor, infos);
	wait_for_all_philosophers(infos);
	pthread_join(id_monitor, NULL);
	return (0);
}
