/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:15:04 by cjulienn          #+#    #+#             */
/*   Updated: 2022/04/21 12:32:41 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	phi_has_died(t_phi *phis, long long i)
{
	display_msg(phis[i].id, DEAD, &phis[i]);
	pthread_mutex_lock(&phis->mutexes->stop_game);
	phis->sim->endgame++;
	pthread_mutex_unlock(&phis->mutexes->stop_game);
}

static void	phis_have_eaten(t_phi *phis, long long i)
{
	display_msg(phis[i].id, VICTORY, &phis[i]);
	pthread_mutex_lock(&phis->mutexes->stop_game);
	phis->sim->endgame++;
	pthread_mutex_unlock(&phis->mutexes->stop_game);
}

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
				phi_has_died(phis, i);
				break ;
			}
			else if (phis->sim->win_num == phis->sim->phi_num)
			{
				phis_have_eaten(phis, i);
				break ;
			}
			i++;
		}
	}
}

/* create phi structs :
=> init all threads using pthread_create
=> put sim->phis_init = 1 (allow simulation to start)
=> use wait_for_endgame func to wait until end of sim
=> join threads
=> launch clean_program to suppress leaks and exit */

static int	init_philos_threads(t_sim *sim)
{
	t_phi				*phis;
	long long			i;
	char				*error_msg;

	error_msg = "unsuccessful memory allocation and/or mutex init error\n";
	phis = init_phi_struct(sim);
	if (!phis)
		return (display_error_msg(error_msg));
	i = 0;
	while (i < sim->phi_num)
	{
		pthread_create(phis[i].thread_id, NULL,
			 &philo_routine, (void *)&phis[i]);
		i++;
	}
	sim->phis_init = 1;
	sim->start = get_time_now();
	wait_for_endgame(phis);
	i = 0;
	while (i < sim->phi_num)
	{
		pthread_join(*phis[i].thread_id, NULL);
		i++;
	}
	return (clean_program(phis));
}

/*  */

int	main(int argc, char **argv)
{
	int			valid;
	t_sim		*sim;

	if (argc != 6 && argc != 5)
		return (display_error_msg("wrong number of arguments\n"));
	valid = check_args_validity(argc, argv); // yet to test
	if (valid == 0)
		return (display_error_msg("invalid argument format\n"));
	sim = (t_sim *)malloc(sizeof(t_sim));
	if (!sim)
		return (display_error_msg("unsuccessful memory allocation\n"));
	init_sim_struct(sim, argv, argc);
	return (init_philos_threads(sim));
}
