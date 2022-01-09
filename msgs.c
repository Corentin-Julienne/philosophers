/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msgs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 12:12:55 by cjulienn          #+#    #+#             */
/*   Updated: 2022/01/09 19:59:47 by cjulienn         ###   ########.fr       */
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
	else
		msg = " has taken a fork\n";
	return (msg);
}

int	display_msg(long long id, int msg_type, t_phi *phi)
{
	char	*msg_content;
	char	*id_to_str;
	char	*time;

	msg_content = obtain_msg(msg_type);
	id_to_str = ft_lltoa(id);
	time = ft_lltoa(phi->sim->time);
	if (!id_to_str || !time)
	{
		display_error_msg("unsuccessful memory allocation\n");
		return (1);
	}
	if (phi->sim->game_over == -1 && phi->sim->victory == -1)
	{
		pthread_mutex_lock(&phi->mutexes->write_msg);
		write(STDOUT_FILENO, time, ft_strlen(time));
		write(STDOUT_FILENO, " ", sizeof(char));
		write(STDOUT_FILENO, id_to_str, ft_strlen(id_to_str));
		write(STDOUT_FILENO, msg_content, ft_strlen(msg_content));
		pthread_mutex_unlock(&phi->mutexes->write_msg);
	}
	free (id_to_str);
	free(time);
	return (0);
}
