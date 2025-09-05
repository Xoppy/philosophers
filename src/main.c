/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc <adi-marc@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:31:35 by adi-marc          #+#    #+#             */
/*   Updated: 2025/09/05 14:41:08 by adi-marc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Start the simulation, wait for threads, and provide the main entry point */
#include "../includes/philo.h"

/* Set start_time and create philosopher and monitor threads */
static int	ft_start(t_philo_env *env)
{
	int	i;

	env->start_time = ft_current_time() + (env->count * 20);
	i = 0;
	while (i < env->count)
	{
		if (pthread_create(&env->philos[i]->thread_id, NULL, ft_routine,
				env->philos[i]) != 0)
			return (0);
		i++;
	}
	if (env->count > 1)
	{
		if (pthread_create(&env->monitor_id, NULL, ft_monitor, env) != 0)
			return (0);
	}
	return (1);
}

/* Wait for philosopher and monitor threads to finish */
static void	ft_wait(t_philo_env *env)
{
	int	i;

	i = 0;
	while (i < env->count)
	{
		pthread_join(env->philos[i]->thread_id, NULL);
		i++;
	}
	if (env->count > 1)
		pthread_join(env->monitor_id, NULL);
}

/* Parse arguments, start threads, wait for completion and clean up */
int	main(int argc, char **argv)
{
	t_philo_env	*env;

	env = ft_init_env(argc, argv);
	if (!env)
		return (1);
	if (!ft_start(env))
	{
		ft_cleanup(env);
		return (1);
	}
	ft_wait(env);
	ft_cleanup(env);
	return (0);
}
