/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc <adi-marc@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:32:03 by adi-marc          #+#    #+#             */
/*   Updated: 2025/09/05 14:41:26 by adi-marc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Implement time utilities */
#include "../includes/philo.h"

/* Get the current time in milliseconds */
long	ft_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/* Sleep for a specified duration while checking the stop flag */
void	ft_sleep_for(t_philo_env *env, long duration)
{
	long	end;
	long	now;
	long	remaining;

	end = ft_current_time() + duration;
	while (1)
	{
		pthread_mutex_lock(&env->stop_lock);
		if (env->stop)
		{
			pthread_mutex_unlock(&env->stop_lock);
			break ;
		}
		pthread_mutex_unlock(&env->stop_lock);
		now = ft_current_time();
		if (now >= end)
			break ;
		remaining = end - now;
		if (remaining > 1000)
			usleep(1000);
		else if (remaining > 200)
			usleep(200);
		else
			usleep(50);
	}
}
