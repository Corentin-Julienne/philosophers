/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msgs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 12:12:55 by cjulienn          #+#    #+#             */
/*   Updated: 2022/01/12 19:25:34 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* function printf_victory_msg to debug only. 
change that before correction process */

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
		msg = " victory condition : ON\n";
	return (msg);
}

static void	print_msg(long long id, int msg_type)
{
	char			*msg_content;
	char			*id_to_str;
	char			*time;

	msg_content = obtain_msg(msg_type);
	id_to_str = ft_lltoa(id);
	time = ft_lltoa(get_time_now());
	if (!id_to_str || !time)
	{
		display_error_msg("unsuccessful memory allocation\n");
		return ;
	}
	write(STDOUT_FILENO, time, ft_strlen(time));
	write(STDOUT_FILENO, " ", sizeof(char));
	write(STDOUT_FILENO, id_to_str, ft_strlen(id_to_str));
	write(STDOUT_FILENO, msg_content, ft_strlen(msg_content));
	free(id_to_str);
	free(time);
}

static void	print_victory_msg(int msg_type)
{
	char	*time;
	char	*msg_content;

	time = ft_lltoa(get_time_now());
	if (!time)
	{
		display_error_msg("unsuccessful memory allocation\n");
		return ;
	}
	msg_content = obtain_msg(msg_type);
	write(STDOUT_FILENO, time, ft_strlen(time));
	write(STDOUT_FILENO, " ", sizeof(char));
	write(STDOUT_FILENO, msg_content, ft_strlen(msg_content));
	free(time);
}

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
			print_victory_msg(msg_type);
			pthread_mutex_unlock(&(phi->mutexes->write_msg));
			return (stop);
		}
		print_msg(id, msg_type);
	}
	pthread_mutex_unlock(&(phi->mutexes->write_msg));
	return (stop);
}
