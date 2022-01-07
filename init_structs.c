/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 13:19:47 by cjulienn          #+#    #+#             */
/*   Updated: 2022/01/07 16:42:04 by cjulienn         ###   ########.fr       */
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
	sim->victory = 0;
	sim->game_over == -1;
	sim->win_cond = -1;
	sim->phis_init = 0;
}

static int	store_mutexes(t_phi *phis, pthread_mutex_t **forks,
	 pthread_mutex_t *write_msg, pthread_mutex_t *add_meal_count)
{
	pthread_mutex_t		*phi_win;
	long long			i;

	pthread_mutex_init(phi_win, NULL);
	i = 0;
	while (i < phis->sim->phi_num)
	{
		phis[i].write_msg = write_msg;
		phis[i].add_meal_count = add_meal_count;
		phis[i].phi_win = phi_win;
		pthread_mutex_init(forks[i], NULL);
		phis[i].r_fork = forks[i];
		if (i > 0)
			phis[i].l_fork = forks[i - 1];
		i++;
	}
	if (phis->sim->phi_num > 1)
		phis[1].l_fork = forks[phis->sim->phi_num - 1];
	else
		phis[1].l_fork = NULL;
	return (0);
}

static int	init_mutexes(t_phi *phis)
{
	pthread_mutex_t		**forks;
	pthread_mutex_t		*write_msg;
	pthread_mutex_t		*add_meal_count;

	forks = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *)
			 * phis->sim->phi_num);
	if (!forks)
		return (display_error_msg("unsuccessful memory allocation\n"));
	pthread_mutex_init(write_msg, NULL);
	pthread_mutex_init(add_meal_count, NULL);
	store_mutexes(phis, forks, write_msg, add_meal_count);
	return (0);
}

static int	store_threads(t_phi *phis)
{
	printf("not implementedc yet !\n");
}

t_phi	*init_phi_struct(t_sim *sim)
{
	t_phi			*phis;
	pthread_t		*thread_ids;
	long long		i;

	phis = (t_phi *)malloc(sizeof(t_phi) * sim->phi_num);
	if (!phis)
		return (NULL);
	thread_ids = (pthread_t *)malloc(sizeof(pthread_t) * sim->phi_num);
	if (!thread_ids)
	{
		free(phis);
		return (NULL);
	}
	i = 0;
	while (i < sim->phi_num)
	{
		phis[i].id = i + 1;
		phis[i].meal_num = 0;
		phis[i].thread_id = thread_ids[i];
		init_mutexes(phis);
		i++;
	}
	return (phis);
}
