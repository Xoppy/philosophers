/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc <adi-marc@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 09:51:27 by adi-marc          #+#    #+#             */
/*   Updated: 2025/09/05 11:19:38 by adi-marc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    ft_message(t_action action, t_philo *philo)
{
    long    time_elapsed;

    time_elapsed = ft_get_time(MILLISECOND) - philo->data->start_time;
    if (philo->is_full || sim_over(philo->data))
        return ;
    pthread_mutex_lock(&philo->data->message_mutex);
    if (action == TAKE_LEFT_FORK || action == TAKE_RIGHT_FORK)
        printf("%ld %d has taken a fork\n", time_elapsed, philo->philo_id);
    else if (action == EAT)
        printf("%ld %d is eating\n", time_elapsed, philo->philo_id);
    else if (action == SLEEP)
        printf("%ld %d is sleeping\n", time_elapsed, philo->philo_id);
    else if (action == THINK)
        printf("%ld %d is thinking\n", time_elapsed, philo->philo_id);
    else if (action == DIE)
        printf("%ld %d died\n", time_elapsed, philo->philo_id);
    pthread_mutex_unlock(&philo->data->message_mutex);
}

