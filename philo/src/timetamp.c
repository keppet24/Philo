/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timetamp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:48:59 by seb               #+#    #+#             */
/*   Updated: 2025/05/31 16:56:22 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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
