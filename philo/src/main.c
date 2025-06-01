/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oettaqi <oettaqi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:55:45 by othmaneetta       #+#    #+#             */
/*   Updated: 2025/06/01 21:28:20 by oettaqi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	part_of_main(t_global_info *infos)
{
	pthread_t		id_monitor;

	pthread_mutex_init(&infos->mutex_finished, NULL);
	pthread_mutex_init(&infos->mutex_info_die_of_philo, NULL);
	pthread_mutex_init(&infos->mutex_on_write, NULL);
	create_philo_and_set_the_table(infos);
	if (pthread_create(&id_monitor, NULL, monitor, infos))
		return (0);
	pthread_join(id_monitor, NULL);
	wait_for_all_philosophers(infos);
	clean_and_destroy(infos);
	return (1);
}

int	main(int ac, char **av)
{
	t_global_info	*infos;

	if (parsing(ac, av) == 0)
		return (0);
	infos = malloc(sizeof(t_global_info));
	if (!infos)
		return (0);
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
	if (part_of_main(infos) == 0)
		return (0);
	return (0);
}
