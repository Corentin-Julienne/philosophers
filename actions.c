/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:33:02 by cjulienn          #+#    #+#             */
/*   Updated: 2022/01/07 16:40:48 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	use_fork(t_phi *phi, int fork_type)
{
	if (fork_type == RIGHT_FORK)
		pthread_mutex_lock(phi->r_fork);
	else
		pthread_mutex_lock(phi->l_fork);
	pthread_mutex_lock(phi->write_msg);
	display_msg(phi->sim->time, phi->id, FORK);
	if (fork_type == LEFT_FORK)
	{
		display_msg(phi->sim->time, phi->id, EATING);
		pthread_mutex_unlock(phi->write_msg);
		phi->last_eat = phi->sim->time;
	}
	else
		pthread_mutex_unlock(phi->write_msg);
}

static void	go_to_sleep(t_phi *phi)
{
	pthread_mutex_lock(phi->write_msg);
	display_msg(phi->sim->time, phi->id, SLEEPING);
	pthread_mutex_unlock(phi->write_msg);
	philo_performing_task(phi->sim->tt_sleep);
}

void	eat_sleep_procedure(t_phi *phi)
{
	use_fork(phi, RIGHT_FORK);
	use_fork(phi, LEFT_FORK);
	philo_performing_task(phi->sim->tt_eat);
	pthread_mutex_unlock(phi->r_fork);
	pthread_mutex_unlock(phi->l_fork);
	phi->meal_num++;
	if (phi->meal_num == phi->sim->win_cond)
	{
		pthread_mutex_lock(phi->phi_win);
		phi->sim->win_num++;
		pthread_mutex_unlock(phi->phi_win);
	}
	go_to_sleep(phi);
	pthread_mutex_lock(phi->write_msg);
	display_msg(phi->sim->time, phi->id, THINKING);
	pthread_mutex_unlock(phi->write_msg);
}
