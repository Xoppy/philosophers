/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc <adi-marc@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:31:41 by adi-marc          #+#    #+#             */
/*   Updated: 2025/09/09 11:47:00 by adi-marc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* Acquire forks in a safe order and log actions */
void	ft_pick_forks(t_philo *philo)
{
	int	first_fork;
	int	second_fork;

	if (philo->left < philo->right)
	{
		first_fork = philo->left;
		second_fork = philo->right;
	}
	else
	{
		first_fork = philo->right;
		second_fork = philo->left;
	}
	pthread_mutex_lock(&philo->env->forks[first_fork]);
	ft_print_state(philo, "has taken a fork");
	pthread_mutex_lock(&philo->env->forks[second_fork]);
	ft_print_state(philo, "has taken a fork");
}

/* Release both forks */
void	ft_drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->env->forks[philo->left]);
	pthread_mutex_unlock(&philo->env->forks[philo->right]);
}
