/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lab.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 18:26:28 by cjulienn          #+#    #+#             */
/*   Updated: 2022/01/08 18:48:01 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lab.h"

void	init_struct(t_phi *phi, int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		phi[i].id = i + 1;
		i++;
	}
}

void	display_stuff(t_phi *phi, int size)
{
	int		i;

	printf("Normal : %lli\n", phi->id);
	
	i = 0;
	while (i < size)
	{
		printf("with index : %lli\n", phi[i].id);
		i++;
	}
}


int main(void)
{
	t_phi	*phi;
	int		size;
	
	size = 8;
	phi = (t_phi*)malloc(sizeof(t_phi) * size);
	if (!phi)
		printf("malloc error\n");
	init_struct(phi, size);
	display_stuff(phi, size);
	return (0);
}