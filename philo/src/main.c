/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:55:45 by othmaneetta       #+#    #+#             */
/*   Updated: 2025/05/31 16:59:20 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int ac, char **av)
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
