/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msgs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 12:12:55 by cjulienn          #+#    #+#             */
/*   Updated: 2022/01/12 11:36:44 by cjulienn         ###   ########.fr       */
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
	return (msg);
}

static void	print_msg(char *time, char *msg_content,
	char *id_to_str, t_phi *phi)
{
	pthread_mutex_lock(&(phi->mutexes->write_msg));
	write(STDOUT_FILENO, time, ft_strlen(time));
	write(STDOUT_FILENO, " ", sizeof(char));
	write(STDOUT_FILENO, id_to_str, ft_strlen(id_to_str));
	write(STDOUT_FILENO, msg_content, ft_strlen(msg_content));
	pthread_mutex_unlock(&(phi->mutexes->write_msg));
}

int	display_msg(long long id, int msg_type, t_phi *phi)
{
	static int		stop = 0;
	char			*msg_content;
	char			*id_to_str;
	char			*time;

	if (msg_type == VICTORY)
		stop++;
	if (stop == 0)
	{
		if (msg_type == DEAD)
			stop++;
		msg_content = obtain_msg(msg_type);
		id_to_str = ft_lltoa(id);
		time = ft_lltoa(get_time_now());
		if (!id_to_str || !time)
		{
			display_error_msg("unsuccessful memory allocation\n");
			return (1);
		}
		print_msg(time, msg_content, id_to_str, phi);
		free (id_to_str);
		free(time);
	}
	return (stop);
}
