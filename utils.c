/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc <adi-marc@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 08:44:41 by adi-marc          #+#    #+#             */
/*   Updated: 2025/09/05 09:49:36 by adi-marc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
Utility functions such as error_exit for when something goes wrong or safe malloc
to avoid rewriting the NULL checker for each malloc

TO DO ----- remove exit with an allowed function to clean up everything.

*/

void    error_exit(const char *err)
{
    printf("%s\n", err);
    exit(EXIT_FAILURE);
}

void    *safe_malloc(size_t bytes)
{
    void    *result;

    result = malloc(bytes);
    if (result == NULL)
        error_exit("Malloc error...");
    return (result);
}

long    ft_get_time(t_timecode timecode)
{
    struct  timeval tv;
    
    if(gettimeofday(&tv, NULL))
        error_exit("Unable to retrieve timecode");
    if (timecode == SECOND)
        return (tv.tv_sec + (tv.tv_usec / 1000000));
    else if (timecode == MILLISECOND)
        return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
    else if (timecode == MICROSECOND)
        return ((tv.tv_sec * 1000000) + tv.tv_usec);
    else
        error_exit("gettimeofday failed...");
    return (1);
}

/*
custom_usleep spinlock to retrieve the correct time that the regulare usleep() 
can't get
*/
void    custom_usleep(long time, t_data *data)
{
    long    start;
    long    time_elapsed;
    long    remaining;

    start = ft_get_time(MICROSECOND);
    while (ft_get_time(MICROSECOND) - start < time)
    {
        if (sim_over(data))
            break ;
        time_elapsed = ft_get_time(MICROSECOND) - start;
        remaining = time - time_elapsed;
        if (remaining < 1000)
            usleep(time % 2);
        else
        {
            while (ft_get_time(MICROSECOND) - start < time)
                ;
        }
    }
}