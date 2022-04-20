/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 13:43:15 by cjulienn          #+#    #+#             */
/*   Updated: 2022/04/20 13:05:05 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_strlen(const char *s)
{
	size_t	counter;

	counter = 0;
	while (s[counter])
		counter++;
	return (counter);
}

long long	calc_res(const char *str)
{
	long long	res;

	if (ft_strlen(str) > 10)
		return (-1);
	res = 0;
	while (str[0])
	{
		res = (res * 10) + (str[0] - '0');
		str++;
	}
	return (res);
}

static char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_protec_strdup(const char *s1)
{
	char				*copy;
	unsigned long		sizer;

	if (!s1)
		return (NULL);
	sizer = ft_strlen(s1) + 1;
	copy = (char *)malloc(sizer * (sizeof(char)));
	if (!(copy))
		return (NULL);
	ft_strcpy(copy, s1);
	return (copy);
}
