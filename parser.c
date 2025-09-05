/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc <adi-marc@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 08:50:31 by adi-marc          #+#    #+#             */
/*   Updated: 2025/09/05 04:40:31 by adi-marc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
This file takes care of everything related to the input parser, it checks if the
given values are withing 0 and INT_MAX, if they contain a char ect... and then
populates the data structure with the values in ms
*/
static  int ft_is_space(char c)
{
    return ((c >= 9 && c <= 13) || c == 32);
}

static int  ft_is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

static const char *valid_number(const char *str)
{
    int len;
    const char  *nbr;

    len = 0;
    while(ft_is_space(*str))
        ++str;
    if (*str == '+')
        ++str;
    else if (*str == '-')
        error_exit("Negative argument detected...");
    if (!ft_is_digit(*str))
        error_exit("Non numeric argument detected...");
    nbr = str;
    while (ft_is_digit(*str))
        ++len;
    if (len > 10)
        error_exit("An argument is too long");
    return (nbr);
}

static long ft_atol(const char *str)
{
    long    nbr;

    nbr = 0;
    str = valid_number(str);
    while (ft_is_digit(*str))
        nbr = (nbr * 10) + (*str++ - 48);
    if (nbr > INT_MAX)
        error_exit("An argument is too long");
    return (nbr);
}

void    parse_input(t_data *data, char **argv)
{
    data->philo_nbr = ft_atol(argv[1]);
    data->time_to_die = ft_atol(argv[2]) * 1000;
    data->time_to_eat = ft_atol(argv[3]) * 1000;
    data->time_to_sleep = ft_atol(argv[4]) * 1000;
    if (argv[5])
        data->meals_limit = ft_atol(argv[5]);
    else
        data->meals_limit = -1;
}
