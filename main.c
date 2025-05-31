/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othmaneettaqi <othmaneettaqi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:55:45 by othmaneetta       #+#    #+#             */
/*   Updated: 2025/05/31 16:24:07 by othmaneetta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

long	timetamp(void)
{
	struct timeval	time;
	long			seconds;
	long			microseconds;
	long			current_time;

	gettimeofday(&time, NULL);
	seconds = time.tv_sec;
	microseconds = time.tv_usec;
	current_time = (seconds * 1000) + (microseconds / 1000);
	return (current_time);
}

void	printf_mutex_thinking(t_philo *philo)
{
	long	delta;

	delta = timetamp() - philo->infos->beginning_of_simulation;
	pthread_mutex_lock(&philo->infos->mutex_on_write);
	printf("[%ld] , [%d] is thinking \n", delta, philo->id + 1);
	pthread_mutex_unlock(&philo->infos->mutex_on_write);
}

void	take_two_fork_even(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex_of_the_fork);
	pthread_mutex_lock(&philo->right_fork->mutex_of_the_fork);
}

void	precise_sleep(long dur_ms)
{
	long start;

	start = timetamp();
	while (timetamp() - start < dur_ms)
		usleep(500);
}

void	drop_the_forks_even(t_philo *philo)
{
	pthread_mutex_unlock(&philo->right_fork->mutex_of_the_fork);
	pthread_mutex_unlock(&philo->left_fork->mutex_of_the_fork);
}

void printf_mutex_sleeping(t_philo *p)
{
    pthread_mutex_lock(&p->infos->mutex_on_write);
    printf("[%ld] , [%d] is sleeping\n",
           timetamp() - p->infos->beginning_of_simulation, p->id + 1);
    pthread_mutex_unlock(&p->infos->mutex_on_write);
    precise_sleep(p->infos->time_to_sleep);
}

void	take_two_forks_odd(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->mutex_of_the_fork);
	pthread_mutex_lock(&philo->left_fork->mutex_of_the_fork);
}

void eating_process(t_philo *p)
{
    /* 1. Marquer le repas IMMÉDIATEMENT */
    pthread_mutex_lock(&p->mutex_info_meal_philo);
    p->numbers_of_meal_eaten++;
    p->last_eating_time = timetamp();                 /* ← ici */
    int meals = p->numbers_of_meal_eaten;             /* garder la valeur pour tester après */
    pthread_mutex_unlock(&p->mutex_info_meal_philo);

    /* 2. Signaler qu’il a atteint la limite */
    if (p->infos->nbr_of_time_each_philo_must_eat != -1 &&
        meals == p->infos->nbr_of_time_each_philo_must_eat)
    {
        pthread_mutex_lock(&p->infos->mutex_finished);
        p->infos->philos_finished++;
        pthread_mutex_unlock(&p->infos->mutex_finished);
    }

    /* 3. Affichages */
    pthread_mutex_lock(&p->infos->mutex_on_write);
    printf("[%ld] , [%d] has taken a fork\n",
           timetamp() - p->infos->beginning_of_simulation, p->id + 1);
    printf("[%ld] , [%d] has taken a fork\n",
           timetamp() - p->infos->beginning_of_simulation, p->id + 1);
    printf("[%ld] , [%d] is eating\n",
           timetamp() - p->infos->beginning_of_simulation, p->id + 1);
    pthread_mutex_unlock(&p->infos->mutex_on_write);

    /* 4. Mastication réelle */
    precise_sleep(p->infos->time_to_eat);
}


void	drop_the_forks_odd(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork->mutex_of_the_fork);
	pthread_mutex_unlock(&philo->right_fork->mutex_of_the_fork);
}

int	routine_even(t_philo *philo)
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

int	routine_odd(t_philo *philo)
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

void	philo_init(t_global_info *infos, int i)
{
	infos->table_of_fork[i].id = i;
	pthread_mutex_init(&(infos->table_of_fork[i].mutex_of_the_fork), NULL);
	infos->table_of_philo[i].id = i;
	infos->table_of_philo[i].left_fork = &infos->table_of_fork[i];
	infos->table_of_philo[i].right_fork = &infos->table_of_fork[(i + 1) % infos->nbr_of_philosophers];
	infos->table_of_philo[i].last_eating_time = infos->beginning_of_simulation;
	infos->table_of_philo[i].numbers_of_meal_eaten = 0;
	infos->table_of_philo[i].infos = infos;
	pthread_mutex_init(&infos->table_of_philo[i].mutex_info_meal_philo, NULL);
}

void	create_philo_and_set_the_table(t_global_info *infos)
{
	int	i;

	i = 0;
	infos->beginning_of_simulation = timetamp();
	infos->table_of_philo = malloc(sizeof(t_philo) * infos->nbr_of_philosophers);
	if (!infos->table_of_philo)
	{
		free(infos->table_of_philo);
		free(infos);
		return ;
	}
	infos->table_of_fork = malloc(sizeof(t_fork) * infos->nbr_of_philosophers);
	if (!infos->table_of_fork)
	{
		free(infos); 
		return ;
	}
	while (i < infos->nbr_of_philosophers)
		philo_init(infos, i++);
	i = 0;
	while (i < infos->nbr_of_philosophers)
	{
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

void	a_philo_died(t_global_info *infos, int i)
{
	pthread_mutex_lock(&infos->mutex_info_die_of_philo);
	infos->a_philo_has_died = 1;
	pthread_mutex_unlock(&infos->mutex_info_die_of_philo);
	pthread_mutex_lock(&infos->mutex_on_write);
	printf("[%ld] , [%d] died \n", timetamp() - infos->beginning_of_simulation, infos->table_of_philo[i].id + 1);
	pthread_mutex_unlock(&infos->mutex_on_write);
	pthread_mutex_unlock(&infos->table_of_philo[i].mutex_info_meal_philo);
}

void *monitor(void *arg)
{
    t_global_info *infos = (t_global_info *)arg;
    long          current_time;
    int           i;

    while (1)
    {
        pthread_mutex_lock(&infos->mutex_finished);
        if (infos->nbr_of_time_each_philo_must_eat != -1 &&
            infos->philos_finished == infos->nbr_of_philosophers)
        {
            pthread_mutex_unlock(&infos->mutex_finished);
            pthread_mutex_lock(&infos->mutex_info_die_of_philo);
            infos->a_philo_has_died = 1;          /* drapeau de fin */
            pthread_mutex_unlock(&infos->mutex_info_die_of_philo);
            return NULL;
        }
        pthread_mutex_unlock(&infos->mutex_finished);
        i = 0;
        while (i < infos->nbr_of_philosophers)
        {
            current_time = timetamp();
            pthread_mutex_lock(&infos->table_of_philo[i].mutex_info_meal_philo);
            if (current_time - infos->table_of_philo[i].last_eating_time >
                infos->time_to_die)
            {
                a_philo_died(infos, i);
                return NULL;
            }
            pthread_mutex_unlock(&infos->table_of_philo[i].mutex_info_meal_philo);
            i++;
        }
        usleep(1000);
    }
}


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

void	*routine_one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf_mutex_thinking(philo);
	return (NULL);
}

void	init_if_one_philo(t_global_info *infos)
{
	pthread_t	id_monitor_thread;

	infos->table_of_fork[0].id = 0;
	pthread_mutex_init(&(infos->table_of_fork[0].mutex_of_the_fork), NULL);
	infos->table_of_philo[0].id = 0;
	infos->table_of_philo[0].left_fork = &infos->table_of_fork[0];
	infos->table_of_philo[0].right_fork = &infos->table_of_fork[0];
	infos->table_of_philo[0].last_eating_time = infos->beginning_of_simulation;
	infos->table_of_philo[0].numbers_of_meal_eaten = 0;
	infos->table_of_philo[0].infos = infos;
	pthread_mutex_init(&infos->table_of_philo[0].mutex_info_meal_philo, NULL);
	pthread_mutex_init(&infos->mutex_on_write, NULL);
	pthread_mutex_init(&infos->mutex_info_die_of_philo, NULL);
	pthread_create(&(infos->table_of_philo[0].id_thread), NULL, routine_one_philo, &(infos->table_of_philo[0]));
	pthread_create(&id_monitor_thread, NULL, monitor, infos);
	pthread_join(id_monitor_thread, NULL);
	pthread_join(infos->table_of_philo[0].id_thread, NULL);
	pthread_mutex_destroy(&infos->table_of_philo[0].mutex_info_meal_philo);
	pthread_mutex_destroy(&infos->table_of_fork[0].mutex_of_the_fork);
	pthread_mutex_destroy(&infos->mutex_on_write);
}

int    one_philo_case(t_global_info *infos)
{
	infos->beginning_of_simulation = timetamp();
	infos->table_of_philo = malloc(sizeof(t_philo));
	if (!infos->table_of_philo)
	{
		free(infos);
		return (0);
	}
	infos->table_of_fork = malloc(sizeof(t_fork));
	if (!infos->table_of_fork)
	{
		free(infos->table_of_philo);
		free(infos);
		return (0); 
	}
	init_if_one_philo(infos);
	free(infos->table_of_philo);
	free(infos->table_of_fork);
	free(infos);
	return (1);
}

int main(int ac, char **av)
{
	t_global_info	*infos;
	pthread_t		id_monitor;

	if (parsing(ac, av) == 0)
		return (0);
	infos = malloc(sizeof(t_global_info));
	infos->nbr_of_philosophers = ft_atoi(av[1]);
	infos->time_to_die = ft_atoi(av[2]);
	infos->time_to_eat = ft_atoi(av[3]);
	infos->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		infos->nbr_of_time_each_philo_must_eat = ft_atoi(av[5]);
	else
		infos->nbr_of_time_each_philo_must_eat = -1;
	infos->a_philo_has_died = 0;
	if (infos->nbr_of_philosophers == 1)
		return (one_philo_case(infos));
	infos->philos_finished = 0;
	pthread_mutex_init(&infos->mutex_finished, NULL);	
	pthread_mutex_init(&infos->mutex_info_die_of_philo, NULL);
	pthread_mutex_init(&infos->mutex_on_write, NULL);
	create_philo_and_set_the_table(infos);
	pthread_create(&id_monitor, NULL, monitor, infos);
	pthread_join(id_monitor, NULL);
	wait_for_all_philosophers(infos);
	clean_and_destroy(infos);
	return (0);
}
