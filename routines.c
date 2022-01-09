/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:00:27 by cjulienn          #+#    #+#             */
/*   Updated: 2022/01/09 20:29:31 by cjulienn         ###   ########.fr       */
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

	sim = (t_sim *)arg;
	while (sim->win_num < sim->win_cond && sim->game_over == -1)
		usleep(1);
	if (sim->win_num >= sim->win_cond)
		sim->victory = get_time_now();
	return (NULL);
}

void	*death_routine(void *arg)
{
	t_phi	*phi;

	phi = (t_phi *)arg;
	usleep(60000); // testing purpose, remove after
	while ((phi->sim->time < (phi->last_eat + phi->sim->tt_die))
		 && phi->sim->victory == -1)
		usleep(1);
	if ((phi->sim->time >= (phi->last_eat + phi->sim->tt_die)))
		phi->sim->game_over = get_time_now();
	if (phi->sim->victory == -1 || (phi->sim->victory != -1
			 && phi->sim->game_over < phi->sim->victory))
		display_msg(phi->id, DEAD, phi);
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_phi			*phi;
	
	phi = (t_phi *)arg;
	while (phi->sim->phis_init == 0)
		usleep(1);
	phi->last_eat = phi->sim->time;
	pthread_create(&(phi->death_id), NULL, &death_routine, (void *)phi);
	if (phi->id % 2 == 0)
		usleep(2000);
	while (phi->sim->victory == -1 && phi->sim->game_over == -1)
		eat_sleep_procedure(phi);
	pthread_join(phi->death_id, NULL);
	return (NULL);
}
