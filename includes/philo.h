/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc <adi-marc@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:32:52 by adi-marc          #+#    #+#             */
/*   Updated: 2025/09/05 14:32:53 by adi-marc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo		t_philo;
typedef struct s_philo_env	t_philo_env;

typedef struct s_philo_env
{
	long					start_time;
	int						stop;
	pthread_mutex_t			stop_lock;
	pthread_mutex_t			write_lock;
	pthread_mutex_t			*forks;
	t_philo					**philos;
	int						count;
	int						death;
	int						eat;
	int						sleep;
	int						meals;
	pthread_t				monitor_id;
}							t_philo_env;

typedef struct s_philo
{
	int						index;
	int						eaten;
	long					last_meal;
	int						left;
	int						right;
	pthread_t				thread_id;
	pthread_mutex_t			meal_lock;
	t_philo_env				*env;
}							t_philo;

/* Parsing and initialization */
int							ft_parse_int(const char *s);
t_philo_env					*ft_create_env(int argc, char **argv);
int							ft_validate_env(t_philo_env *env, int argc);
t_philo_env					*ft_init_env(int argc, char **argv);
void						ft_cleanup(t_philo_env *env);

/* Time utilities */
long						ft_current_time(void);
void						ft_sleep_for(t_philo_env *env, long duration);

/* Stop flag utilities */
void						ft_request_stop(t_philo_env *env);
int							ft_is_stopped(t_philo_env *env);

/* Output printing */
void						ft_print_state(t_philo *philo, const char *msg);

/* Fork handling */
void						ft_pick_forks(t_philo *philo);
void						ft_drop_forks(t_philo *philo);

/* Philosopher actions */
void						ft_eat(t_philo *philo);
void						ft_rest(t_philo *philo);
void						ft_think(t_philo *philo, int silent);
void						*ft_single_life(void *arg);

/* Philosopher routine */
void						*ft_routine(void *arg);

/* Monitor thread */
int							ft_check_philo_status(t_philo_env *env, int i,
								int *full_count);
void						*ft_monitor(void *arg);

#endif
