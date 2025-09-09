/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc <adi-marc@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:31:38 by adi-marc          #+#    #+#             */
/*   Updated: 2025/09/09 10:33:27 by adi-marc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* Update meal time, print eating message, sleep, and increment meal count */
void	ft_eat(t_philo *philo)
{
	ft_print_state(philo, "is eating");
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = ft_current_time();
	pthread_mutex_unlock(&philo->meal_lock);
	ft_sleep_for(philo->env, philo->env->eat);
	if (!ft_is_stopped(philo->env))
	{
		pthread_mutex_lock(&philo->meal_lock);
		philo->eaten += 1;
		pthread_mutex_unlock(&philo->meal_lock);
	}
}

/* Print sleeping message and sleep for the configured duration */
void	ft_rest(t_philo *philo)
{
	ft_print_state(philo, "is sleeping");
	ft_sleep_for(philo->env, philo->env->sleep);
}

/* Calculate thinking time, optionally log it, then pause */
void	ft_think(t_philo *philo, int silent)
{
	long	now;
	long	remaining;
	long	think_time;

	pthread_mutex_lock(&philo->meal_lock);
	now = ft_current_time();
	remaining = philo->env->death - (now - philo->last_meal) - philo->env->eat;
	pthread_mutex_unlock(&philo->meal_lock);
	think_time = remaining / 2;
	if (think_time < 0)
		think_time = 0;
	if (think_time == 0 && silent)
		think_time = 1;
	if (think_time > 600)
		think_time = 200;
	if (!silent)
		ft_print_state(philo, "is thinking");
	ft_sleep_for(philo->env, think_time);
}

/* Routine for a single philosopher */
void	*ft_single_life(void *arg)
{
	t_philo		*philo;
	t_philo_env	*env;

	philo = (t_philo *)arg;
	env = philo->env;
	ft_print_state(philo, "has taken a fork");
	ft_sleep_for(env, env->death);
	pthread_mutex_lock(&env->write_lock);
	printf("%ld %d died\n", ft_current_time() - env->start_time, philo->index
		+ 1);
	pthread_mutex_unlock(&env->write_lock);
	ft_request_stop(env);
	return (NULL);
}
