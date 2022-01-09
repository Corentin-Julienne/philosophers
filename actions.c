/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:33:02 by cjulienn          #+#    #+#             */
/*   Updated: 2022/01/09 20:02:40 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	handle_left_fork(t_phi *phi, int action)
{
	if (action == LOCK_FORK)
	{
		if (phi->sim->phi_num > 1 && phi->id != 1)
			pthread_mutex_lock(&phi->mutexes->forks[phi->id - 2]);
		else if (phi->sim->phi_num > 1 && phi->id == 1)
			pthread_mutex_lock(&phi->mutexes->forks[0]);	
	}
	else
	{
		if (phi->sim->phi_num > 1 && phi->id != 1)
			pthread_mutex_unlock(&phi->mutexes->forks[phi->id - 2]);
		else if (phi->sim->phi_num > 1 && phi->id == 1)
			pthread_mutex_unlock(&phi->mutexes->forks[0]);	
	}
	return (0);
}

static int	use_fork(t_phi *phi, int fork_type)
{
	if (phi->sim->victory != -1 || phi->sim->game_over != -1)
		return (1);
	if (fork_type == RIGHT_FORK)
		pthread_mutex_lock(&phi->mutexes->forks[phi->id - 1]); // r_fork
	else
		handle_left_fork(phi, LOCK_FORK);
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
	pthread_mutex_unlock(&phi->mutexes->forks[phi->id - 1]);
	handle_left_fork(phi, UNLOCK_FORK);
	phi->meal_num++;
	if (phi->meal_num == phi->sim->win_cond)
	{
		pthread_mutex_lock(&(phi->mutexes->phi_win));
		phi->sim->win_num++;
		pthread_mutex_unlock(&(phi->mutexes->phi_win));
	}
	display_msg(phi->id, SLEEPING, phi);
	philo_performing_task(phi->sim->tt_sleep, phi);
	display_msg(phi->id, THINKING, phi);
}
