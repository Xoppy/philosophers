/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc <adi-marc@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:01:35 by adi-marc          #+#    #+#             */
/*   Updated: 2025/09/05 11:15:48 by adi-marc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
This file takes care of the data initialisation by populating the t_philo
structure for each philosophers and the the data structure with the starting
values, it also takes care of the forks by assigning to each philo the right
forks based on even and odd positioning. It also allocates the required memory
for each philo and fork to exist. Finally, it initialize the fork mutexes.
*/
static void forks_init(t_philo *philo, t_fork *forks, int pos)
{
    int philo_nbr;

    philo_nbr = philo->data->philo_nbr;
    philo->left_fork = &forks[pos];
    philo->right_fork = &forks[(pos + 1) % philo_nbr];
    if (philo->philo_id % 2 == 0)
    {
        philo->right_fork = &forks[pos];
        philo->left_fork = &forks[(pos + 1) % philo_nbr];
    }
    
}

static void philo_init(t_data *data)
{
    int i;
    t_philo *philo;

    i = -1;
    while(++i < data->philo_nbr)
    {
        philo = data->philos + i;
        philo->philo_id = i + 1;
        philo->is_full = false;
        philo->meals_eaten = 0;
        philo->data = data;
        pthread_mutex_init(&philo->philo_mutex, NULL);
        forks_init(philo, data->forks, i);
    }
}

void    data_init(t_data *data)
{
    int i;
    
    i = -1;
    data->simulation_over = false;
    data->philo_initialized = false;
    pthread_mutex_init(&data->data_mutex, NULL);
    pthread_mutex_init(&data->message_mutex, NULL);
    data->philos = safe_malloc(sizeof(t_philo) * data->philo_nbr);
    data->forks = safe_malloc(sizeof(t_fork) * data->philo_nbr);
    while (++i < data->philo_nbr)
    {
        pthread_mutex_init(&data->forks[i].fork, NULL);
        data->forks[i].fork_id = i;
    }
    philo_init(data);
}
