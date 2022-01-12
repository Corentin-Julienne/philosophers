/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:15:04 by cjulienn          #+#    #+#             */
/*   Updated: 2022/01/12 11:30:18 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	wait_for_endgame(t_phi *phis)
{
	long long		i;

	while (!phis->sim->endgame)
	{
		i = 0;
		while (i < phis->sim->phi_num)
		{
			if ((get_time_now() >= (phis[i].last_eat + phis->sim->tt_die))
				 && phis[i].last_eat != -1)
			{
				display_msg(phis[i].id, DEAD, &phis[i]);
				pthread_mutex_lock(&phis->mutexes->stop_game);
				phis->sim->endgame++;
				pthread_mutex_unlock(&phis->mutexes->stop_game);
			}
			else if (phis->sim->win_num == phis->sim->phi_num)
			{
				display_msg(phis[i].id, VICTORY, &phis[i]);
				pthread_mutex_lock(&phis->mutexes->stop_game);
				phis->sim->endgame++;
				pthread_mutex_unlock(&phis->mutexes->stop_game);
			}
			i++;
		}
	}
}

int	init_philos_threads(t_sim *sim)
{
	t_phi				*phis;
	long long			i;

	phis = init_phi_struct(sim);
	if (!phis)
		return (display_error_msg("unsuccessful memory allocation\n"));
	i = 0;
	while (i < sim->phi_num)
	{
		pthread_create(phis[i].thread_id, NULL,
			 &philo_routine, (void *)&phis[i]);
		i++;
	}
	sim->phis_init = 1;
	wait_for_endgame(phis);
	i = 0;
	while (i < sim->phi_num)
	{
		pthread_join(*phis[i].thread_id, NULL);
		i++;
	}
	return (leak_killing(sim, phis));
}

int	main(int argc, char **argv)
{
	int			valid;
	t_sim		*sim;

	if (argc != 6 && argc != 5)
		return (display_error_msg("wrong number of arguments\n"));
	valid = check_args_validity(argc, argv);
	if (valid == 1)
		return (display_error_msg("invalid argument format\n"));
	sim = (t_sim *)malloc(sizeof(t_sim));
	if (!sim)
		return (display_error_msg("unsuccessful memory allocation\n"));
	init_sim_struct(sim, argv, argc);
	return (init_philos_threads(sim));
}
