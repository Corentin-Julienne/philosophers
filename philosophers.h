/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:15:00 by cjulienn          #+#    #+#             */
/*   Updated: 2022/04/20 17:47:36 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

# define THINKING		0
# define EATING			1
# define SLEEPING		2
# define DEAD			3
# define VICTORY		4
# define FORK			5

# define RIGHT_FORK		1
# define LEFT_FORK		2

typedef struct s_sim
{
	int					phi_num;
	int					tt_die;
	int					tt_eat;
	int					tt_sleep;
	int					win_cond;
	int					win_num;
	int					phis_init;
	long long			start;
	int					endgame;
	pthread_t			*thread_ids;
}						t_sim;

typedef struct s_phi
{
	long long			id;
	long long			last_eat;
	long long			meal_num;
	pthread_t			*thread_id;
	pthread_t			*death_id;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
	t_sim				*sim;
	struct s_mutexes	*mutexes;
}						t_phi;

typedef struct s_mutexes
{
	pthread_mutex_t		write_msg;
	pthread_mutex_t		add_meal_count;
	pthread_mutex_t		phi_win;
	pthread_mutex_t		stop_game;
	pthread_mutex_t		*forks;
}						t_mutexes;

/* actions.c */
int					eat_sleep_procedure(t_phi *phi_by_id);
/* check_args.c */
int					check_args_validity(int argc, char **argv);
/* errors.c */
int					display_error_msg(const char *err_specific);
/* free.c */
int					clean_program(t_phi *phis);
/* init_structs.c */
void				init_sim_struct(t_sim *sim, char **argv, int argc);
t_phi				*init_phi_struct(t_sim *sim);
/* msgs.c */
int					display_msg(long long id, int msg_type, t_phi *phi);
/* mutexes.c */
t_mutexes			*init_mutexes_struct(t_sim *sim);
/* routines */
void				*philo_routine(void *arg);
/* time.c */
void				custom_usleep(long long time);
void				algo_phi_wait(t_phi *phi);
int					is_dead(long long last_eat, long long tt_die);
long long			get_time_now(void);
int					philo_performing_task(int duration, t_phi *phi);
/* utils_1.c */
int					ft_isdigit(char c);
size_t				ft_strlen(const char *s);
long long			calc_res(const char *str);
char				*ft_protec_strdup(const char *s1);
/* utils_2.c */
char				*ft_lltoa(long long n);
/* utils_3.c */
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
char				*ft_strjoin_and_free(const char *s1, const char *s2);
char				*ft_strjoin(char const *s1, char const *s2);

#endif
