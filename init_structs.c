/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 13:19:47 by cjulienn          #+#    #+#             */
/*   Updated: 2021/12/29 14:10:26 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_sim_struct(t_sim *sim, char **argv, int argc)
{
	sim->phi_num = calc_res(argv[1]);
	sim->fork_num = sim->phi_num;
	sim->tt_die = calc_res(argv[2]);
	sim->tt_eat = calc_res(argv[3]);
	sim->tt_sleep = calc_res(argv[4]);
	if (argc == 6)
		sim->num_of_meal = calc_res(argv[5]);
	else
		sim->num_of_meal = -1;
}
