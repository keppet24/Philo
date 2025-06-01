/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oettaqi <oettaqi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:58:31 by othmaneetta       #+#    #+#             */
/*   Updated: 2025/06/01 21:43:16 by oettaqi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_philo	t_philo;

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	mutex_of_the_fork;
}				t_fork;

typedef struct s_global_info
{
	int				nbr_of_philosophers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nbr_of_time_each_philo_must_eat;
	long			beginning_of_simulation;
	t_fork			*table_of_fork;
	t_philo			*table_of_philo;
	int				a_philo_has_died;
	pthread_mutex_t	mutex_info_die_of_philo;
	pthread_mutex_t	mutex_on_write;
	int				philos_finished;
	pthread_mutex_t	mutex_finished;
}				t_global_info;

typedef struct s_philo
{
	int				id;
	long			last_eating_time;
	int				numbers_of_meal_eaten;
	pthread_t		id_thread;
	t_fork			*right_fork;
	t_fork			*left_fork;
	pthread_mutex_t	mutex_info_meal_philo;
	t_global_info	*infos;
}				t_philo;

int		parsing(int ac, char **av);
int		ft_atoi(char *s1);
int		one_philo_case(t_global_info *infos);
void	*monitor(void *arg);
void	clean_and_destroy(t_global_info *infos);
void	create_philo_and_set_the_table(t_global_info *infos);
void	a_philo_died(t_global_info *infos, int i);
void	wait_for_all_philosophers(t_global_info *infos);
void	philo_init(t_global_info *infos, int i);
void	*routine(void *arg);
void	drop_the_forks_odd(t_philo *philo);
void	drop_the_forks_even(t_philo *philo);

void	eating_process(t_philo *p);
void	take_two_forks_odd(t_philo *philo);
void	printf_mutex_sleeping(t_philo *p);
void	precise_sleep(long dur_ms);
void	printf_mutex_thinking(t_philo *philo);
long	timetamp(void);
int		simulation_is_not_ended(t_philo *philo);
void	take_two_fork_even(t_philo *philo);
int		ft_isdigit(int c);
#endif