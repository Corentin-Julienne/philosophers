/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:15:04 by cjulienn          #+#    #+#             */
/*   Updated: 2021/12/29 17:18:28 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*timer(t_sim *sim)
{
	struct timeval	*timer;

	while (42)
	{
		timer = (struct timeval *)malloc(sizeof(struct timeval));
		if (!timer)
			break; // TODO with better solution
		gettimeofday(&timer, NULL);
		update_timestamp(sim, timer);
		free(timer);
	}
}

void	update_timestamp(t_sim *sim, struct timeval *timer)
{
	useconds_t	current;
	useconds_t	start;

	current = ft_timestamp(timer->tv_sec, timer->tv_sec);
	start = sim->start;
	sim->chrono = current - start;
}

int	philo(t_sim *sim)
{
	t_phi			*phi;
	struct timeval	*timer;
	long long		i;

	timer = (struct timeval *)malloc(sizeof(struct timeval));
	if (!timer)
		return (-1); // TODO
	gettimeofday(&timer, NULL);
	
	i = 0;
	while (i < sim->phi_num)
	{
		
		init_phi(sim, i);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int			valid;
	int			rtn;
	t_sim		*sim;
	
	if (argc != 6 && argc != 5)
	{
		write(2, "philosophers : error : wrong number of arguments\n", 49);
		return (1);
	}
	valid = check_args_validity(argc, argv);
	if (valid == 1)
	{
		write(2, "philosophers : error : invalid argument format\n", 47);
		return (1);
	}
	sim = (t_sim *)malloc(sizeof(t_sim));
	if (!sim)
		return (-1); // change that
	init_sim_struct(sim, argv);
	rtn = philo(sim);
	return (rtn);
}
