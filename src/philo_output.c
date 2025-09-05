/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc <adi-marc@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:31:52 by adi-marc          #+#    #+#             */
/*   Updated: 2025/09/05 14:41:18 by adi-marc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Printing utilities */
#include "../includes/philo.h"

/* Print the timestamp, philosopher ID and a message */
void	ft_print_state(t_philo *philo, const char *msg)
{
	long	timestamp;

	pthread_mutex_lock(&philo->env->write_lock);
	if (!ft_is_stopped(philo->env))
	{
		timestamp = ft_current_time() - philo->env->start_time;
		printf("%ld %d %s\n", timestamp, philo->index + 1, msg);
	}
	pthread_mutex_unlock(&philo->env->write_lock);
}
