/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:33:02 by cjulienn          #+#    #+#             */
/*   Updated: 2022/01/08 19:18:04 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	use_fork(t_phi *phi, int fork_type)
{
	if (phi->sim->victory != -1 || phi->sim->game_over != -1)
		return (1);
	if (fork_type == RIGHT_FORK)
		pthread_mutex_lock(&phi->r_fork);
	else
		pthread_mutex_lock(&phi->l_fork);
	display_msg(phi->id, FORK, phi);
	if (fork_type == LEFT_FORK)
	{
		display_msg(phi->id, EATING, phi);
		phi->last_eat = phi->sim->time;
	}
	return (0);
}

void	eat_sleep_procedure(t_phi *phi)
{
	use_fork(phi, RIGHT_FORK);
	use_fork(phi, LEFT_FORK);
	philo_performing_task(phi->sim->tt_eat, phi);
	pthread_mutex_unlock(&phi->r_fork);
	pthread_mutex_unlock(&phi->l_fork);
	phi->meal_num++;
	if (phi->meal_num == phi->sim->win_cond)
	{
		pthread_mutex_lock(&phi->phi_win);
		phi->sim->win_num++;
		pthread_mutex_unlock(&phi->phi_win);
	}
	display_msg(phi->id, SLEEPING, phi);
	philo_performing_task(phi->sim->tt_sleep, phi);
	display_msg(phi->id, THINKING, phi);
}
