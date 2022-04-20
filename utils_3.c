/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:56:29 by cjulienn          #+#    #+#             */
/*   Updated: 2022/04/19 15:33:18 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static size_t	ft_count_size_dest(char *dst, size_t n)
{
	size_t		res;
	size_t		size;
	char		*d;

	d = (char *)dst;
	res = 0;
	size = n;
	while (*d != '\0' && size != 0)
	{
		res++;
		d++;
		size--;
	}
	return (res);
}

static size_t	ft_total_counter(char *dst, const char *src, size_t n)
{
	size_t		res;

	res = ft_strlen(src) + ft_count_size_dest(dst, n);
	if (n < ft_count_size_dest(dst, n))
		res = ft_strlen(src) + n;
	return (res);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t						total_counter;
	size_t						n;
	const unsigned char			*s;
	unsigned char				*d;

	s = (const unsigned char *)src;
	d = (unsigned char *)dst;
	n = dstsize;
	total_counter = ft_total_counter(dst, src, n);
	if (n == 0 || (n <= (ft_count_size_dest(dst, n))))
		return (total_counter);
	while (n-- && *d != '\0' && n != 0)
		d++;
	while (*s != '\0')
	{
		if (n != 0)
		{
			*d++ = *s;
			n--;
		}
		s++;
	}
	if (n >= 0)
		*d = '\0';
	return (total_counter);
}

char	*ft_strjoin_and_free(const char *s1, const char *s2)
{
	char			*copy;
	size_t			i;
	size_t			j;

	if (!s1 || !s2)
		return (NULL);
	copy = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1)
		* (sizeof(char)));
	if (!copy)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		copy[i++] = s2[j++];
	copy[i] = '\0';
	free((void *)s1);
	s1 = NULL;
	return (copy);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*copy;
	size_t			i;
	size_t			j;

	if (!s1 || !s2)
		return (NULL);
	copy = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1)
		* (sizeof(char)));
	if (!(copy))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		copy[i] = s2[j];
		i++;
		j++;
	}
	copy[i] = '\0';
	return (copy);
}
