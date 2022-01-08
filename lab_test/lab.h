/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lab.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 18:26:30 by cjulienn          #+#    #+#             */
/*   Updated: 2022/01/08 18:48:36 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LAB_H
# define LAB_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_sim
{
	long long			phi_num;
	long long			tt_die;
	long long			tt_eat;
	long long			tt_sleep;
	pthread_t			chronometer;
	pthread_t			monitor_meals;
}						t_sim;


typedef struct s_phi
{
	long long			id;
	pthread_mutex_t		*r_fork;
	pthread_t			thread_id;
}						t_phi;

#endif