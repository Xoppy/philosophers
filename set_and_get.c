/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_and_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc <adi-marc@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:22:24 by adi-marc          #+#    #+#             */
/*   Updated: 2025/09/05 04:46:16 by adi-marc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
This file containg utility functions in order to set and get the correct mutex
for our structures.
*/
void    set_bool(pthread_mutex_t *mutex, bool *destination, bool value)
{
    pthread_mutex_lock(mutex);
    *destination = value;
    pthread_mutex_unlock(mutex);
}

bool    get_bool(pthread_mutex_t *mutex, bool *value)
{
    bool    ret;

    pthread_mutex_lock(mutex);
    ret = *value;
    pthread_mutex_unlock(mutex);
    return (ret);
}

void    set_long(pthread_mutex_t *mutex, long *destination, long value)
{
    pthread_mutex_lock(mutex);
    *destination = value;
    pthread_mutex_unlock(mutex);
}

long    get_long(pthread_mutex_t *mutex, long *value)
{
    long    ret;

    pthread_mutex_lock(mutex);
    ret = *value;
    pthread_mutex_unlock(mutex);
    return (ret);
}

bool    sim_over(t_data *data)
{
    return (get_bool(&data->data_mutex, &data->simulation_over));
}