/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 16:47:12 by cjulienn          #+#    #+#             */
/*   Updated: 2022/04/20 13:34:02 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* create an array of forks/mutexes (one by philo) 
and init them */

static pthread_mutex_t	*init_forks(t_sim *sim)
{
	pthread_mutex_t		*forks;
	int					i;

	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			 * sim->phi_num);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < sim->phi_num)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			free(forks); // destroy forks to avoid leaks ?
			return (NULL);
		}
		i++;
	}
	return (forks);
}

/* init all the non-fok mutexes useful for the simulation */

static int	init_mutexes(t_mutexes *mutexes)
{
	pthread_mutex_t		write_msg;
	pthread_mutex_t		add_meal_count;
	pthread_mutex_t		phi_win;
	pthread_mutex_t		stop_game;

	if (pthread_mutex_init(&write_msg, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&add_meal_count, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&phi_win, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&stop_game, NULL) != 0)
		return (1);
	mutexes->write_msg = write_msg;
	mutexes->add_meal_count = add_meal_count;
	mutexes->phi_win = phi_win;
	mutexes->stop_game = stop_game;
	return (0);
}

t_mutexes	*init_mutexes_struct(t_sim *sim)
{
	t_mutexes			*mutexes;
	pthread_mutex_t		*forks;

	mutexes = (t_mutexes *)malloc(sizeof(t_mutexes));
	if (!mutexes)
		return (NULL);
	forks = init_forks(sim);
	if (!forks)
	{
		free(mutexes);
		return (NULL);
	}
	mutexes->forks = forks;
	if (init_mutexes(mutexes) == 1)
	{
		free(mutexes);
		free(forks);
		return (NULL);
	}
	return (mutexes);
}
