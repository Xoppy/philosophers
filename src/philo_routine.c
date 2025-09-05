/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc <adi-marc@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:31:57 by adi-marc          #+#    #+#             */
/*   Updated: 2025/09/05 14:41:22 by adi-marc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Philosopher routine */
#include "../includes/philo.h"

/* Main loop executed by each philosopher */
void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = philo->env->start_time;
	pthread_mutex_unlock(&philo->meal_lock);
	while (ft_current_time() < philo->env->start_time)
		usleep(50);
	if (philo->env->death <= 0 || philo->env->meals == 0)
		return (NULL);
	if (philo->env->count == 1)
		return (ft_single_life(arg));
	if ((philo->index % 2) == 1)
		ft_think(philo, 1);
	while (!ft_is_stopped(philo->env))
	{
		ft_pick_forks(philo);
		ft_eat(philo);
		ft_print_state(philo, "is sleeping");
		ft_drop_forks(philo);
		ft_sleep_for(philo->env, philo->env->sleep);
		ft_think(philo, 0);
	}
	return (NULL);
}
