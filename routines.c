/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:00:27 by cjulienn          #+#    #+#             */
/*   Updated: 2022/01/11 12:44:26 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void	*victory_routine(void *arg)
{
	t_phi	*phis;

	phis = (t_phi *)arg;
	while (phis->sim->win_num < phis->sim->win_cond)
		usleep(1000);
	display_msg(phis->id, VICTORY, phis);
	return (NULL);
}

void	*death_routine(void *arg)
{
	t_phi	*phi;

	phi = (t_phi *)arg;
	while (get_time_now() < (phi->last_eat + phi->sim->tt_die))
		usleep(1000);
	display_msg(phi->id, DEAD, phi);
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_phi			*phi;
	int				res_func;

	phi = (t_phi *)arg;
	res_func = 0;
	while (phi->sim->phis_init == 0)
		usleep(1000);
	phi->last_eat = get_time_now();
	pthread_create(phi->death_id, NULL, &death_routine, arg);
	if (phi->id % 2 == 0)
		usleep(1000000);
	while (!res_func)
		res_func = eat_sleep_procedure(phi);
	pthread_join(*phi->death_id, NULL);
	return (NULL);
}
