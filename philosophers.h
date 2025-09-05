/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc <adi-marc@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 08:30:01 by adi-marc          #+#    #+#             */
/*   Updated: 2025/09/05 11:07:17 by adi-marc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>

typedef enum    e_timecode
{
    SECOND,
    MILLISECOND,
    MICROSECOND,
}   t_timecode;

typedef enum    e_action
{
    EAT,
    SLEEP,
    THINK,
    TAKE_LEFT_FORK,
    TAKE_RIGHT_FORK,
    DIE,
}   t_action;

typedef struct s_fork  t_fork;
typedef struct s_data  t_data;
typedef struct s_philo t_philo;

typedef struct s_philo
{
    int philo_id;
    long    meals_eaten;
    bool    is_full;
    long    last_meal_eaten;
    t_fork  *left_fork;
    t_fork  *right_fork;
    pthread_mutex_t philo_mutex;
    pthread_t   thread_id;
    t_data  *data;
}   t_philo;

typedef struct  s_fork
{
    pthread_mutex_t fork;
    int fork_id;
}   t_fork;

typedef struct s_data
{
    long    philo_nbr;
    long    time_to_die;
    long    time_to_eat;
    long    time_to_sleep;
    long    meals_limit;
    long    start_time;
    bool    simulation_over;
    bool    philo_initialized;
    pthread_mutex_t   data_mutex;
    pthread_mutex_t   message_mutex;
    t_fork  *forks;
    t_philo *philos;
}   t_data;

// utils.c
void    error_exit(const char *err);
void    *safe_malloc(size_t bytes);
long    ft_get_time(t_timecode timecode);
void    custom_usleep(long usec, t_data *data);

// parser.c
void    parse_input(t_data *data, char **argv);

// initialize.c
void    data_init(t_data *data);

// set_and_get.c
void    set_bool(pthread_mutex_t *mutex, bool *destination, bool value);
bool    get_bool(pthread_mutex_t *mutex, bool *value);
void    set_long(pthread_mutex_t *mutex, long *destination, long value);
long    get_long(pthread_mutex_t *mutex, long *value);
bool    sim_over(t_data *data);

// sync_utils.c
void    wait_threads(t_data *data);

// status.c
void    ft_message(t_action action, t_philo *philo);

// simulation.c
void    sim_start(t_data *data);