/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 13:19:47 by cjulienn          #+#    #+#             */
/*   Updated: 2022/04/20 13:32:33 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_sim_struct(t_sim *sim, char **argv, int argc)
{
	sim->phi_num = (int)calc_res(argv[1]);
	sim->tt_die = (int)calc_res(argv[2]);
	sim->tt_eat = (int)calc_res(argv[3]);
	sim->tt_sleep = (int)calc_res(argv[4]);
	if (argc == 6)
		sim->win_cond = (int)calc_res(argv[5]);
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
		return (1);
	sim->thread_ids = thread_ids;
	i = 0;
	while (i < sim->phi_num)
	{
		phis[i].thread_id = &thread_ids[i];
		i++;
	}
	return (0);
}

static void	setup_phis(t_phi *phis, t_mutexes *mutexes, t_sim *sim)
{
	long long		i;

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
}

t_phi	*init_phi_struct(t_sim *sim)
{
	t_phi			*phis;
	t_mutexes		*mutexes;

	phis = (t_phi *)malloc(sizeof(t_phi) * sim->phi_num);
	if (!phis)
		return (NULL);
	mutexes = init_mutexes_struct(sim);
	if (!mutexes)
	{
		free(phis);
		return (NULL);
	}
	if (store_threads(phis, sim) != 0)
	{
		free(phis);
		free(mutexes);
		return (NULL);
	}
	setup_phis(phis, mutexes, sim);
	return (phis);
}
