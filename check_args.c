/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:35:03 by cjulienn          #+#    #+#             */
/*   Updated: 2022/04/20 13:33:36 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* check if every char is a digit */

static int	is_pos_number(const char *str)
{
	int		error;
	int		i;

	error = 0;
	i = 0;
	while (str && str[i])
	{
		if (str[i] < '0'|| str[i] > '9')
			error++;
		i++;
	}
	if (error > 0)
		return (0);
	return (1);
}

/* check if a given string is composed of numbers,
then check if this number is less than UINT_MAX,
return 1 if num valid, 0 otherwise */

static int	is_unsint_convertible(const char *str)
{
	long long			res;

	if (is_pos_number(str) == 0)
		return (0);
	res = calc_res(str);
	if (res == -1)
		return (0);
	if (res > INT_MAX)
		return (0);
	return (1);
}

/* check the validity of args, 
return 1 if all args are convertible to unsigned int,
0 otherwise */

int	check_args_validity(int argc, char **argv)
{
	if (is_unsint_convertible(argv[1]) == 0)
		return (0);
	if (is_unsint_convertible(argv[2]) == 0)
		return (0);
	if (is_unsint_convertible(argv[3]) == 0)
		return (0);
	if (is_unsint_convertible(argv[4]) == 0)
		return (0);
	if (argc == 6)
	{
		if (is_unsint_convertible(argv[5]) == 1)
			return (0);
	}
	return (1);
}
