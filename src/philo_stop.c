/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_stop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc <adi-marc@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:32:00 by adi-marc          #+#    #+#             */
/*   Updated: 2025/09/09 10:33:38 by adi-marc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* Set the stop flag to 1 */
void	ft_request_stop(t_philo_env *env)
{
	pthread_mutex_lock(&env->stop_lock);
	env->stop = 1;
	pthread_mutex_unlock(&env->stop_lock);
}

/* Return 1 if the simulation has stopped */
int	ft_is_stopped(t_philo_env *env)
{
	int	stopped;

	pthread_mutex_lock(&env->stop_lock);
	stopped = env->stop;
	pthread_mutex_unlock(&env->stop_lock);
	return (stopped);
}
