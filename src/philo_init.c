/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc <adi-marc@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:31:44 by adi-marc          #+#    #+#             */
/*   Updated: 2025/09/09 13:22:18 by adi-marc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* Allocate and initialize philosopher structures */
int	ft_setup_philos(t_philo_env *env)
{
	int	i;

	env->philos = (t_philo **)malloc(sizeof(t_philo *) * env->count);
	if (!env->philos)
		return (0);
	i = 0;
	while (i < env->count)
	{
		env->philos[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!env->philos[i])
			return (0);
		env->philos[i]->index = i;
		env->philos[i]->eaten = 0;
		env->philos[i]->left = i;
		env->philos[i]->right = (i + 1) % env->count;
		if ((i % 2) == 1)
		{
			env->philos[i]->left = (i + 1) % env->count;
			env->philos[i]->right = i;
		}
		env->philos[i]->env = env;
		pthread_mutex_init(&env->philos[i]->meal_lock, NULL);
		i++;
	}
	return (1);
}

/* Allocate forks and initialize mutex locks */
int	ft_setup_mutexes(t_philo_env *env)
{
	int	i;

	env->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* env->count);
	if (!env->forks)
		return (0);
	i = 0;
	while (i < env->count)
	{
		if (pthread_mutex_init(&env->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	if (pthread_mutex_init(&env->write_lock, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&env->stop_lock, NULL) != 0)
		return (0);
	return (1);
}

/* Helper to init environment fields */
static void	ft_init_env_fields(t_philo_env *env)
{
	env->stop = 0;
	env->forks = NULL;
	env->philos = NULL;
	env->start_time = 0;
}

/* Parse arguments, validate them and set up the environment */
t_philo_env	*ft_init_env(int argc, char **argv)
{
	t_philo_env	*env;

	if (argc != 5 && argc != 6)
		return (NULL);
	env = ft_create_env(argc, argv);
	if (!env)
		return (NULL);
	if (!ft_validate_env(env, argc))
	{
		free(env);
		return (NULL);
	}
	ft_init_env_fields(env);
	if (!ft_setup_mutexes(env))
	{
		ft_cleanup(env);
		return (NULL);
	}
	if (!ft_setup_philos(env))
	{
		ft_cleanup(env);
		return (NULL);
	}
	return (env);
}
