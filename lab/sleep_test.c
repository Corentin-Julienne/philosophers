/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:57:45 by cjulienn          #+#    #+#             */
/*   Updated: 2022/04/20 17:39:06 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

/*
** Returns the timestamp in milliseconds
*/

long    get_time(void)
{
    struct timeval  tp;
    long            milliseconds;

    gettimeofday(&tp, NULL);
    milliseconds = tp.tv_sec * 1000;
    milliseconds += tp.tv_usec / 1000;
    return (milliseconds);
}

void	custom_usleep(long time)
{
	long start = get_time();

	while (42)
    {
        if (get_time() - start >= time)
            break ;
        usleep(50);
    }
}

/*
** Prints time, sleeps 200ms, repeats!
*/

int main(void)
{
    long start_time;
		
		// Remember when we started
    start_time = get_time();

    while (1)
    {
				// Print time from start, in ms
        printf("%ld\n", get_time() - start_time);

				// Sleep 200 times 1000 microseconds (1 millisecond)
		custom_usleep(200);
    }
}
