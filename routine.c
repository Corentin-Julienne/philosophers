/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:00:27 by cjulienn          #+#    #+#             */
/*   Updated: 2022/01/12 19:01:58 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void	*philo_routine(void *arg)
{
	t_phi			*phi;
	int				res_func;

	phi = (t_phi *)arg;
	res_func = 0;
	while (phi->sim->phis_init == 0)
		usleep(1); // change that
	phi->last_eat = get_time_now();
	algo_phi_wait(phi);
	while (!res_func)
		res_func = eat_sleep_procedure(phi);
	return (NULL);
}
