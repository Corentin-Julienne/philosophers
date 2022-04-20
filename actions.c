/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:33:02 by cjulienn          #+#    #+#             */
/*   Updated: 2022/04/20 13:07:17 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* die_alone is used when there is only one philosopher
there is also one fork so philo cannot eat, 
so he is starving to death. Sad. */

static int	die_alone(t_phi *phi)
{
	pthread_mutex_lock(phi->r_fork);
	while (is_dead(phi->last_eat, phi->sim->tt_die) == 0)
		usleep(1);
	display_msg(1, DEAD, phi);
	pthread_mutex_unlock(phi->r_fork);
	return (1);
}

/* allow a philosophers to release forks/mutexes
in case of pb. So others phis can eat */

static int	pb_release_forks(t_phi *phi)
{
	pthread_mutex_unlock(phi->r_fork);
	pthread_mutex_unlock(phi->l_fork);
	return (1);
}

/* use when a philosopher wanna eat 
=> lock both forks/mutexes
=> display msg "has taken a fork"
=> update phi->last_eat 
=> realease forks if display msg problem */

static int	request_forks(t_phi *phi)
{
	int		i;

	pthread_mutex_lock(phi->r_fork);
	pthread_mutex_lock(phi->l_fork);
	i = 0;
	while (i < 2)
	{
		if (display_msg(phi->id, FORK, phi) != 0)
			return (pb_release_forks(phi));
		i++;
	}
	phi->last_eat = get_time_now();
	if (display_msg(phi->id, EATING, phi) != 0)
		return (pb_release_forks(phi));
	return (0);
}

/* in the eat/sleep procedure, a philo will :
1) request forks 
2) eat
3) release forks
4) add the total meal absorbed
5) go to sleep and print sleeping msg
6) wait while sleeping
7) go thinking and print thinking msg */

int	eat_sleep_procedure(t_phi *phi)
{
	if (phi->sim->phi_num == 1)
		return (die_alone(phi));
	if (request_forks(phi) != 0)
		return (1);
	if (philo_performing_task(phi->sim->tt_eat, phi) != 0)
		return (pb_release_forks(phi));
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
	if (philo_performing_task(phi->sim->tt_sleep, phi) != 0)
		return (1);
	if (display_msg(phi->id, THINKING, phi) != 0)
		return (1);
	return (0);
}
