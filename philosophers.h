/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:15:00 by cjulienn          #+#    #+#             */
/*   Updated: 2022/01/08 18:59:12 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define THINKING		0
# define EATING			1
# define SLEEPING		2
# define DEAD			3
# define FORK			4

# define RIGHT_FORK		1
# define LEFT_FORK		2

typedef struct s_sim
{
	long long			phi_num;
	long long			tt_die;
	long long			tt_eat;
	long long			tt_sleep;
	long long			start;
	long long			time;
	long long			win_cond;
	long long			win_num;
	long long			game_over;
	long long			victory;
	int					phis_init;
	pthread_t			chronometer;
	pthread_t			monitor_meals;
}						t_sim;

typedef struct s_phi
{
	long long			id;
	long long			last_eat;
	long long			meal_num;
	pthread_mutex_t		r_fork;
	pthread_mutex_t		l_fork;
	pthread_mutex_t		write_msg;
	pthread_mutex_t		add_meal_count;
	pthread_mutex_t		phi_win;
	pthread_t			thread_id;
	pthread_t			death_id;
	t_sim				*sim;
}						t_phi;

/* actions.c */
void				eat_sleep_procedure(t_phi *phi_by_id);
/* check_args.c */
int					check_args_validity(int argc, char **argv);
/* errors.c */
int					display_error_msg(const char *err_specific);
/* free.c */
int					leak_killing(t_sim *sim, t_phi *phis);
/* init_structs.c */
void				init_sim_struct(t_sim *sim, char **argv, int argc);
t_phi				*init_phi_struct(t_sim *sim);
/* msgs.c */
int					display_msg(long long id, int msg_type, t_phi *phi);
/* philosophers.c */
int					init_philos_threads(t_sim *sim);
/* routines */
void				*chrono(void *arg);
void				*victory_routine(void *arg);
void				*death_routine(void *arg);
void				*philo_routine(void *arg);
/* time.c */
long long			get_time_now(void);
void				philo_performing_task(long long duration, t_phi *phi);
/* utils_1.c */
int					ft_isdigit(char c);
size_t				ft_strlen(const char *s);
long long			calc_res(const char *str);
/* utils_2.c */
char				*ft_lltoa(long long n);

#endif
