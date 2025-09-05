/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc <adi-marc@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 06:52:30 by adi-marc          #+#    #+#             */
/*   Updated: 2025/09/05 07:16:03 by adi-marc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
sync_utils contains a spinlock function to wait for all the philos to be ready
before starting the simulation
*/
void    wait_threads(t_data *data)
{
    while(!get_bool(&data->data_mutex, &data->philo_initialized))
        ;
    return ;
}