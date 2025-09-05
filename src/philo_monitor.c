/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc <adi-marc@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:31:49 by adi-marc          #+#    #+#             */
/*   Updated: 2025/09/05 14:41:16 by adi-marc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Monitor the philosophers for death or full meals */
#include "../includes/philo.h"

/* Helper for the monitor thread; returns 1 if a philosopher dies */
int	ft_check_philo_status(t_philo_env *env, int i, int *full_count)
{
	long	now;

	pthread_mutex_lock(&env->philos[i]->meal_lock);
	now = ft_current_time();
	if ((now - env->philos[i]->last_meal) >= env->death)
	{
		pthread_mutex_unlock(&env->philos[i]->meal_lock);
		pthread_mutex_lock(&env->write_lock);
		printf("%ld %d died\n", now - env->start_time, i + 1);
		pthread_mutex_unlock(&env->write_lock);
		ft_request_stop(env);
		return (1);
	}
	if (env->meals > 0 && env->philos[i]->eaten >= env->meals)
		(*full_count)++;
	pthread_mutex_unlock(&env->philos[i]->meal_lock);
	return (0);
}

/* Monitor thread to detect death and meal completion */
void	*ft_monitor(void *arg)
{
	t_philo_env	*env;
	int			i;
	int			full_count;

	env = (t_philo_env *)arg;
	if (env->meals == 0)
		return (NULL);
	while (ft_current_time() < env->start_time)
		usleep(50);
	while (!ft_is_stopped(env))
	{
		i = 0;
		full_count = 0;
		while (i < env->count)
		{
			if (ft_check_philo_status(env, i, &full_count))
				return (NULL);
			i++;
		}
		if (env->meals > 0 && full_count == env->count)
		{
			ft_request_stop(env);
			return (NULL);
		}
		usleep(500);
	}
	return (NULL);
}
