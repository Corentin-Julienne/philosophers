/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_conv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 16:43:08 by cjulienn          #+#    #+#             */
/*   Updated: 2021/12/29 16:54:29 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

useconds_t	sec_to_usec(time_t sec)
{
	useconds_t		res;
	
	res = sec * 1000;
	return (res);
}

useconds_t	microsec_to_usec(suseconds_t microsec)
{
	useconds_t		res;

	res = microsec / 1000;
	return (res);
}

useconds_t	ft_timestamp(time_t sec, suseconds_t microsec)
{
	useconds_t		timestamp;
	
	timestamp = sec_to_usec(sec) + microsec_to_usec(microsec);
	return (timestamp);
}
