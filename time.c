/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 16:43:08 by cjulienn          #+#    #+#             */
/*   Updated: 2022/01/12 19:24:08 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// static int	custom_usleep(long long duration)
// {
// 	if (duration < 1000000)
// 	{
// 		if (usleep(duration) != 0)
// 			return (1);
// 	}	
// 	else
// 	{
// 		if (usleep(99999) != 0)
// 			return (1);
// 		custom_usleep(duration - 99999);
// 	}
// 	return (0);
// }

int	is_dead(long long last_eat, long long tt_die)
{
	if (get_time_now() >= last_eat + tt_die)
		return (1);
	else
		return (0);
}

void	algo_phi_wait(t_phi *phi)
{
	if (phi->id % 2 == 0)
		usleep(phi->sim->tt_die);
}

long long	get_time_now(void)
{
	struct timeval		timestamp;

	gettimeofday(&timestamp, NULL);
	return ((timestamp.tv_sec * 1000) + (timestamp.tv_usec / 1000));
}

int	philo_performing_task(long long duration, t_phi *phi)
{
	long long	time;

	time = get_time_now();
	while ((get_time_now() < (time + duration)))
	{
		if (is_dead(phi->last_eat, phi->sim->tt_die) == 1)
		{
			display_msg(phi->id, DEAD, phi);
			pthread_mutex_lock(&phi->mutexes->stop_game);
			phi->sim->endgame++;
			pthread_mutex_unlock(&phi->mutexes->stop_game);
			return (1);
		}
		if (phi->sim->win_num == phi->sim->win_cond)
		{
			display_msg(phi->id, VICTORY, phi);
			pthread_mutex_lock(&phi->mutexes->stop_game);
			phi->sim->endgame++;
			pthread_mutex_unlock(&phi->mutexes->stop_game);
			return (1);
		}
		usleep(phi->sim->phi_num * 2); // keep that in place
	}
	return (0);
}
