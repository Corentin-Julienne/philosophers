/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:35:03 by cjulienn          #+#    #+#             */
/*   Updated: 2021/12/29 14:04:17 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* check if str is convertible to usecs format for later use with usleep func in C */

static int	is_number(const char *str)
{
	int		error;
	int		i;

	error = 0;
	i = 0;
	while (str && str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			error++;
		i++;
	}
	if (error > 0)
		return (1);
	return (0);
}

unsigned long long calc_res(const char *str)
{
	unsigned long long		res;

	res = 0;
	while (str[0])
	{
		res = (res * 10) + (str[0] - '0');
		str++;
	}
	return (res);
}

static int	is_usec_convertible(const char *str)
{
	unsigned long long		res;

	if (is_number(str) == 1)
		return (1);
	res = calc_res(str);
	if (res > 1000000)
		return (1);
	return (0);
}

static int	is_unsint_convertible(const char *str)
{
	unsigned long long		res;

	if (is_number(str) == 1)
		return (1);
	res = calc_res(str);
	if (res >= 9223372036854775808ULL)
		return (1);
	return (0);
}

int	check_args_validity(int argc, char **argv)
{
	if (is_usint_convertible(argv[1]) == 1)
		return (1);
	if (is_usec_convertible(argv[2]) == 1)
		return (1);
	if (is_usec_convertible(argv[3]) == 1)
		return (1);
	if (is_usec_convertible(argv[4]) == 1)
		return (1);
	if (argc == 6)
	{
		if (is_usint_convertible(argv[5]) == 1)
			return (1);
	}
	return (0);
}
