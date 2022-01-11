/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:33:02 by cjulienn          #+#    #+#             */
/*   Updated: 2022/01/11 12:02:05 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	use_fork(t_phi *phi, int fork_type)
{
	if (fork_type == RIGHT_FORK)
		pthread_mutex_lock(phi->r_fork);
	else
		pthread_mutex_lock(phi->l_fork);
	if (display_msg(phi->id, FORK, phi) != 0)
		return (1);
	if (fork_type == LEFT_FORK)
	{
		if (display_msg(phi->id, EATING, phi) != 0)
			return (1);
		phi->last_eat = get_time_now();
	}
	return (0);
}

int	eat_sleep_procedure(t_phi *phi)
{
	if (use_fork(phi, RIGHT_FORK) != 0)
		return (1);
	if (use_fork(phi, LEFT_FORK) != 0)
		return (1);
	philo_performing_task(phi->sim->tt_eat);
	pthread_mutex_unlock(phi->r_fork);
	pthread_mutex_unlock(phi->l_fork);
	phi->meal_num++;
	if (phi->meal_num == phi->sim->win_cond)
	{
		pthread_mutex_lock(&(phi->mutexes->phi_win));
		phi->sim->win_num++;
		pthread_mutex_unlock(&(phi->mutexes->phi_win));
	}
	if (display_msg(phi->id, SLEEPING, phi) != 0)
		return (1);
	philo_performing_task(phi->sim->tt_sleep);
	if (display_msg(phi->id, THINKING, phi) != 0)
		return (1);
	return (0);
}
