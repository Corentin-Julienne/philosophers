/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 16:43:08 by cjulienn          #+#    #+#             */
/*   Updated: 2022/01/08 14:47:43 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_time_now(void)
{
	struct timeval		timestamp;

	gettimeofday(&timestamp, NULL);
	return ((timestamp.tv_sec / 1000) + (timestamp.tv_usec + 1000));
}

void	philo_performing_task(long long duration, t_phi *phi)
{
	long long	time;

	time = get_time_now();
	while (get_time_now() < (time + duration) && phi->sim->victory == -1
		 && phi->sim->game_over == -1)
		usleep(1);
}
