/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 13:19:47 by cjulienn          #+#    #+#             */
/*   Updated: 2022/01/11 20:04:26 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_sim_struct(t_sim *sim, char **argv, int argc)
{
	sim->phi_num = calc_res(argv[1]);
	sim->tt_die = calc_res(argv[2]);
	sim->tt_eat = calc_res(argv[3]);
	sim->tt_sleep = calc_res(argv[4]);
	if (argc == 6)
		sim->win_cond = calc_res(argv[5]);
	else
		sim->win_cond = -1;
	sim->win_num = 0;
	sim->phis_init = 0;
	sim->endgame = 0;
}

static int	store_threads(t_phi *phis, t_sim *sim)
{
	pthread_t		*thread_ids;
	long long		i;

	thread_ids = (pthread_t *)malloc(sizeof(pthread_t) * sim->phi_num);
	if (!thread_ids)
		return (display_error_msg("unsuccessful memory allocation\n"));
	i = 0;
	while (i < sim->phi_num)
	{
		phis[i].thread_id = &thread_ids[i];
		i++;
	}
	return (0);
}

t_phi	*init_phi_struct(t_sim *sim)
{
	t_phi			*phis;
	t_mutexes		*mutexes;
	long long		i;

	phis = (t_phi *)malloc(sizeof(t_phi) * sim->phi_num);
	mutexes = init_mutexes_struct(sim);
	if (!phis || !mutexes)
		return (NULL);
	store_threads(phis, sim);
	i = 0;
	while (i < sim->phi_num)
	{
		phis[i].sim = sim;
		phis[i].mutexes = mutexes;
		phis[i].id = i + 1;
		phis[i].meal_num = 0;
		phis[i].last_eat = -1;
		phis[i].r_fork = &phis->mutexes->forks[i];
		if (phis->sim->phi_num != 1 && i > 0)
			phis[i].l_fork = &phis->mutexes->forks[i - 1];
		else if (phis->sim->phi_num != 1 && i == 0)
			phis[i].l_fork = &phis->mutexes->forks[phis->sim->phi_num - 1];
		i++;
	}
	return (phis);
}
