/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msgs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 12:12:55 by cjulienn          #+#    #+#             */
/*   Updated: 2022/04/20 16:34:18 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static char	*obtain_msg(int msg_type)
{
	char		*msg;

	if (msg_type == THINKING)
		msg = " is thinking\n";
	else if (msg_type == EATING)
		msg = " is eating\n";
	else if (msg_type == SLEEPING)
		msg = " is sleeping\n";
	else if (msg_type == DEAD)
		msg = " died\n";
	else if (msg_type == FORK)
		msg = " has taken a fork\n";
	else
		msg = " every philosopher has eaten enough pasta\n";
	return (msg);
}

static void	assemble_msg(char *msg_content, char *id_to_str,
	char *time)
{
	char	*full_msg;
	char	*tmp;
	
	full_msg = ft_strjoin(time, " ");
	free(time);
	if (!full_msg)
		; // handle this
	tmp = ft_strjoin(full_msg, id_to_str);
	free(full_msg);
	if (!tmp)
		; // handle this
	full_msg = ft_strjoin(tmp, msg_content);
	free(tmp);
	if (!full_msg)
		; // handle this
	if (write(STDOUT_FILENO, full_msg, ft_strlen(full_msg)) == -1)
		; // handle this
}

static void	print_msg(long long id, int msg_type, t_sim *sim)
{
	char			*msg_content;
	char			*id_to_str;
	char			*time;

	time = ft_lltoa(get_time_now() - sim->start);
	if (!time)
	{
		display_error_msg("unsuccessful memory allocation\n"); // change this
		return ;
	}
	id_to_str = ft_lltoa(id);
	if (!id_to_str)
	{
		free(time);
		display_error_msg("unsuccessful memory allocation\n"); // change this
		return ;
	}
	msg_content = obtain_msg(msg_type);
	assemble_msg(msg_content, id_to_str, time);
	free(id_to_str);
}

static void	print_victory_msg(int msg_type, t_sim *sim)
{
	char	*time;
	char	*msg_content;
	char	*full_msg;
	char 	*tmp;

	time = ft_lltoa(get_time_now() - sim->start);
	if (!time)
	{
		display_error_msg("unsuccessful memory allocation\n");
		return ;
	}
	msg_content = obtain_msg(msg_type);
	tmp = ft_strjoin(time, " ");
	free(time);
	if (!tmp)
		; // handle this
	full_msg = ft_strjoin(tmp, msg_content);
	free(tmp);
	if (!full_msg)
		; // handle this
	if (write(STDOUT_FILENO, full_msg, ft_strlen(full_msg)) == -1)
		; // handle this
	free(full_msg);
}

/* 
display msg function will print a msg for a changing state
(eat, sleep, think, dead, victory). The stop static variable,
shared by all thread,
is used a bareer to prevent multiple phi
to win the game or die at the same time 
 */

int	display_msg(long long id, int msg_type, t_phi *phi)
{
	static int		stop = 0;

	pthread_mutex_lock(&(phi->mutexes->write_msg));
	if (stop == 0)
	{
		if (msg_type == DEAD || msg_type == VICTORY)
			stop++;
		if (msg_type == VICTORY)
		{
			print_victory_msg(msg_type, phi->sim);
			pthread_mutex_unlock(&(phi->mutexes->write_msg));
			return (stop);
		}
		print_msg(id, msg_type, phi->sim);
	}
	pthread_mutex_unlock(&(phi->mutexes->write_msg));
	return (stop);
}
