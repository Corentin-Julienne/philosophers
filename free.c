/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:32:34 by cjulienn          #+#    #+#             */
/*   Updated: 2022/01/12 18:42:26 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	rm_mutexes(t_phi *phis)
{
	long long		i;
	
	pthread_mutex_destroy(&phis->mutexes->add_meal_count);
	pthread_mutex_destroy(&phis->mutexes->phi_win);
	pthread_mutex_destroy(&phis->mutexes->stop_game);
	pthread_mutex_destroy(&phis->mutexes->write_msg);
	i = 0;
	while (i < phis->sim->phi_num)
	{
		pthread_mutex_destroy(&phis->mutexes->forks[i]);
		i++;
	}
}

int	clean_program(t_phi *phis)
{
	rm_mutexes(phis);
	free(phis->mutexes->forks);
	free(phis->mutexes);
	free(phis->sim->thread_ids);
	free(phis->sim);
	free(phis);
	return (0);
}
