/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:33:02 by cjulienn          #+#    #+#             */
/*   Updated: 2022/01/12 11:28:55 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	request_forks(t_phi *phi)
{
	int		i;

	pthread_mutex_lock(phi->r_fork);
	pthread_mutex_lock(phi->l_fork);
	i = 0;
	while (i < 2)
	{
		if (display_msg(phi->id, FORK, phi) != 0)
		{
			pthread_mutex_unlock(phi->r_fork);
			pthread_mutex_unlock(phi->l_fork);
			return (1);
		}
		i++;
	}
	phi->last_eat = get_time_now();
	if (display_msg(phi->id, EATING, phi) != 0)
		return (1);
	return (0);
}

int	eat_sleep_procedure(t_phi *phi)
{
	if (request_forks(phi) != 0)
		return (1);
	philo_performing_task(phi->sim->tt_eat, phi);
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
	philo_performing_task(phi->sim->tt_sleep, phi);
	if (display_msg(phi->id, THINKING, phi) != 0)
		return (1);
	return (0);
}
