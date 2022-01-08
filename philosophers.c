/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:15:04 by cjulienn          #+#    #+#             */
/*   Updated: 2022/01/08 14:28:41 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_monitoring_threads(t_sim *sim)
{
	pthread_t			*chronometer;
	pthread_t			*monitor_meals;

	pthread_create(chronometer, NULL, &chrono, (void *)sim);
	if (sim->win_cond != -1)
		pthread_create(monitor_meals, NULL, &victory_routine, (void *)sim);
	sim->chronometer = chronometer;
	sim->monitor_meals = monitor_meals;
	return (0);
}

int	init_philos_threads(t_sim *sim)
{
	t_phi				*phis;
	long long			i;

	phis = init_phi_struct(sim);
	if (!phis)
		return (display_error_msg("unsuccessful memory allocation\n"));
	i = 0;
	init_monitoring_threads(sim);
	while (i < sim->phi_num)
	{
		pthread_create(&(phis[i].thread_id), NULL,
			 &philo_routine, &phis[i]);
		i++;
	}
	sim->phis_init = 1;
	i = 0;
	while (i < sim->phi_num)
	{
		pthread_join(phis[i].thread_id, NULL);
		i++;
	}
	pthread_join(*(sim->monitor_meals), NULL);
	pthread_join(*(sim->chronometer), NULL);
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
