/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc <adi-marc@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:54:42 by adi-marc          #+#    #+#             */
/*   Updated: 2025/09/05 11:09:01 by adi-marc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void philo_eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->left_fork->fork);
    ft_message(TAKE_LEFT_FORK, philo);
    pthread_mutex_lock(&philo->right_fork->fork);
    ft_message(TAKE_RIGHT_FORK, philo);
    set_long(&philo->philo_mutex, &philo->last_meal_eaten, ft_get_time(MILLISECOND));
    philo->meals_eaten++;
    ft_message(EAT, philo);
    custom_usleep(philo->data->time_to_eat, philo->data);
    if (philo->data->meals_limit > 0 && philo->meals_eaten == philo->data->meals_limit)
        set_bool(&philo->philo_mutex, &philo->is_full, true);
    pthread_mutex_unlock(&philo->left_fork->fork);
    pthread_mutex_unlock(&philo->right_fork->fork);
}

static void philo_think(t_philo *philo)
{
    ft_message(THINK, philo);
}

void    *dinner_sim(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;
    wait_threads(philo->data);
    while (!sim_over(philo->data))
    {
        if (philo->is_full)
            break ;
        philo_eat(philo);
        ft_message(SLEEP, philo);
        custom_usleep(philo->data->time_to_sleep, philo->data);
        philo_think(philo);
    }
    return (NULL);
}

void    sim_start(t_data *data)
{
    int i;

    i = -1;
    if (data->meals_limit == 0)
        return ;
    else if (data->philo_nbr == 1)
        return;    // to do
    else
    {
        while (++i < data->philo_nbr)
            pthread_create(&data->philos[i].thread_id,NULL, dinner_sim, &data->philos[i]);
    }
    data->start_time = ft_get_time(MILLISECOND);
    set_bool(&data->data_mutex, &data->philo_initialized, true);
    i = -1;
    while (++i < data->philo_nbr)
        pthread_join(data->philos[i].thread_id, NULL);
}