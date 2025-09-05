/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc <adi-marc@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:31:54 by adi-marc          #+#    #+#             */
/*   Updated: 2025/09/05 14:41:20 by adi-marc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Parsing utilities */
#include "../includes/philo.h"

/* Convert a numeric string to an int; returns -1 on error */
int	ft_parse_int(const char *s)
{
	long	num;
	int		i;

	num = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] < '0' || s[i] > '9')
			return (-1);
		num = num * 10 + (s[i] - '0');
		if (num > 2147483647)
			return (-1);
		i++;
	}
	return ((int)num);
}

/* Allocate and fill a philosopher environment from arguments */
t_philo_env	*ft_create_env(int argc, char **argv)
{
	t_philo_env	*env;
	int			meals_temp;

	(void)argc;
	env = (t_philo_env *)malloc(sizeof(t_philo_env));
	if (!env)
		return (NULL);
	env->count = ft_parse_int(argv[1]);
	env->death = ft_parse_int(argv[2]);
	env->eat = ft_parse_int(argv[3]);
	env->sleep = ft_parse_int(argv[4]);
	env->meals = -1;
	if (argc == 6)
	{
		meals_temp = ft_parse_int(argv[5]);
		env->meals = meals_temp;
	}
	return (env);
}

/* Validate parsed values to ensure they are within acceptable bounds */
int	ft_validate_env(t_philo_env *env, int argc)
{
	if (env->count <= 0 || env->count > 250)
		return (0);
	if (env->death <= 0 || env->eat < 0 || env->sleep < 0)
		return (0);
	if (argc == 6 && env->meals < 0)
		return (0);
	return (1);
}
