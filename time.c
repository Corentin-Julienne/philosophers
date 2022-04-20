/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 16:43:08 by cjulienn          #+#    #+#             */
/*   Updated: 2022/04/20 17:59:30 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* accurate usleep function
features a loop of usleep(50) with verif after each iteration 
!!! time in milliseconds !!!*/

void	custom_usleep(long long time)
{
	long long		start;

	start = get_time_now();
	while (42)
	{
		if (get_time_now() - start >= time)
			break ;
		usleep(50);
	}
}

int	is_dead(long long last_eat, long long tt_die)
{
	if (get_time_now() >= last_eat + tt_die)
		return (1);
	else
		return (0);
}

void	algo_phi_wait(t_phi *phi) // change and complete this
{
	if (phi->id % 2 == 0)
		custom_usleep(phi->sim->tt_die * 1000);
}

/* used to get the current timestamp !!! unit is milliseconds !!! */

long long	get_time_now(void)
{
	struct timeval		timestamp;

	gettimeofday(&timestamp, NULL);
	return ((timestamp.tv_sec * 1000) + (timestamp.tv_usec / 1000));
}

int	philo_performing_task(int duration, t_phi *phi)
{
	long long			time;

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
		custom_usleep(phi->sim->phi_num * 2); // keep that in place
	}
	return (0);
}
