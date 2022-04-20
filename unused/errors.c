/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:32:55 by cjulienn          #+#    #+#             */
/*   Updated: 2022/01/08 15:19:41 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	display_error_msg(const char *err_specific)
{
	char		*err_general;

	err_general = "philosophers : error : ";
	write(STDERR_FILENO, err_general, ft_strlen(err_general));
	write(STDERR_FILENO, err_specific, ft_strlen(err_specific));
	return (1);
}
