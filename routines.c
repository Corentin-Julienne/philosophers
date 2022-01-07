/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:00:27 by cjulienn          #+#    #+#             */
/*   Updated: 2022/01/07 16:45:31 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void	*chrono(void *arg)
{
	t_sim	*sim;

	sim = (t_sim *)arg;
	while (sim->phis_init == 0)
		usleep(1);
	sim->start = get_time_now();
	while (sim->victory == -1 && sim->game_over == -1)
	{
		sim->time = get_time_now();
		usleep(1);
	}
	return (NULL);
}

void	*victory_routine(void *arg)
{
	t_sim	*sim;

	sim = (t_sim *)sim;
	while (sim->win_num < sim->win_cond && sim->game_over == -1)
		usleep(1);
	if (sim->win_num >= sim->win_num)
		sim->victory = get_time_now();
	return (NULL);
}

void	*death_routine(void *arg)
{
	t_phi	*phi;

	phi = (t_phi *)arg;
	while ((phi->sim->time < (phi->last_eat + phi->sim->tt_die))
		 && phi->sim->victory == -1)
		usleep(1);
	if ((phi->sim->time >= (phi->last_eat + phi->sim->tt_die)))
		phi->sim->game_over == get_time_now();
	if (phi->sim->victory == -1 || (phi->sim->victory != -1
			 && phi->sim->game_over < phi->sim->victory))
	{
		pthread_mutex_lock(phi->write_msg);
		display_msg(phi->sim->time, phi->id, DEAD);
		pthread_mutex_unlock(phi->write_msg);
	}
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_phi	*phi;

	phi = (t_phi *)arg;
	while (phi->sim->phis_init == 0)
		usleep(1);
	while (phi->sim->victory == 1 && phi->sim->game_over == -1)
	{
		while (phi->sim->win_num < phi->sim->win_cond)
			eat_sleep_procedure(phi);
	}
	return (NULL);
}
