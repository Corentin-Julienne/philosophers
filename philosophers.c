/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:15:04 by cjulienn          #+#    #+#             */
/*   Updated: 2022/01/09 20:07:42 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	display_phis(t_phi *phis) // test function only
{
	long long					i;
	
	i = 0;
	while (i < phis->sim->phi_num)
	{
		printf("id             : %lli\n" ,phis[i].id);
		printf("phi_num        : %lli\n", phis[i].sim->phi_num);
		printf("last eat       : %lli\n" ,phis[i].last_eat);
		printf("meal num       : %lli\n" ,phis[i].meal_num);
		printf("tt_die         : %lli\n", phis[i].sim->tt_die);	
		printf("----------------------\n\n");
		i++;
	}
	return (0);
}

int	init_monitoring_threads(t_sim *sim)
{
	pthread_t			chronometer;
	pthread_t			monitor_meals;

	monitor_meals = NULL;
	pthread_create(&chronometer, NULL, &chrono, (void *)sim);
	if (sim->win_cond != -1)
		pthread_create(&monitor_meals, NULL, &victory_routine, (void *)sim);
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
	// display_phis(phis);
	init_monitoring_threads(sim);
	i = 0;
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
	pthread_join(sim->monitor_meals, NULL);
	pthread_join(sim->chronometer, NULL);
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
