/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc <adi-marc@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:31:41 by adi-marc          #+#    #+#             */
/*   Updated: 2025/09/05 14:41:12 by adi-marc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Fork handling functions */
#include "../includes/philo.h"

/* Acquire forks in a safe order and log actions */
void	ft_pick_forks(t_philo *philo)
{
	if ((philo->index % 2) == 0)
	{
		pthread_mutex_lock(&philo->env->forks[philo->left]);
		ft_print_state(philo, "has taken a fork");
		pthread_mutex_lock(&philo->env->forks[philo->right]);
		ft_print_state(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->env->forks[philo->right]);
		ft_print_state(philo, "has taken a fork");
		pthread_mutex_lock(&philo->env->forks[philo->left]);
		ft_print_state(philo, "has taken a fork");
	}
}

/* Release both forks */
void	ft_drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->env->forks[philo->left]);
	pthread_mutex_unlock(&philo->env->forks[philo->right]);
}
