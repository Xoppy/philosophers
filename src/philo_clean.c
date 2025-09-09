/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc <adi-marc@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 10:41:32 by adi-marc          #+#    #+#             */
/*   Updated: 2025/09/09 10:42:18 by adi-marc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* Helper to destroy forks */
static void	ft_destroy_forks(t_philo_env *env)
{
	int	i;

	if (!env->forks)
		return ;
	i = 0;
	while (i < env->count)
	{
		pthread_mutex_destroy(&env->forks[i]);
		i++;
	}
	free(env->forks);
}

/* Helper to destroy philosophers */
static void	ft_destroy_philos(t_philo_env *env)
{
	int	i;

	if (!env->philos)
		return ;
	i = 0;
	while (i < env->count)
	{
		if (env->philos[i])
		{
			pthread_mutex_destroy(&env->philos[i]->meal_lock);
			free(env->philos[i]);
		}
		i++;
	}
	free(env->philos);
}

/* Destroy mutexes and free allocated memory */
void	ft_cleanup(t_philo_env *env)
{
	if (!env)
		return ;
	ft_destroy_forks(env);
	ft_destroy_philos(env);
	pthread_mutex_destroy(&env->write_lock);
	pthread_mutex_destroy(&env->stop_lock);
	free(env);
}
