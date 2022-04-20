/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:32:55 by cjulienn          #+#    #+#             */
/*   Updated: 2022/04/19 18:31:57 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	display_error_msg(const char *err_specific)
{
	char		*err_general;

	err_general = ft_strjoin("philosophers : error : ", err_specific);
	if (!err_general)
		; // handle this
	write(STDERR_FILENO, err_general, ft_strlen(err_general));
	return (1);
}
