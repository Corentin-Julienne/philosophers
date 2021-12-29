/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:15:00 by cjulienn          #+#    #+#             */
/*   Updated: 2021/12/29 17:09:23 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <time.h> // check if necessary

typedef struct s_sim
{
	unsigned long long	phi_num;
	unsigned long long	fork_num;
	useconds_t			start;
	useconds_t			current;
	useconds_t			chrono;
	useconds_t			tt_die;
	useconds_t			tt_eat;
	useconds_t			tt_sleep;
	long long			num_of_meal;
}						t_sim;

typedef struct s_phi
{
	int				id;
	int				alive;
	int				status;
	int				meal_num;
	struct s_phi	*right;
	struct s_phi	*left;
}				t_phi;

#endif
