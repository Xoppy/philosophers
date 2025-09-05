/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc <adi-marc@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 08:29:55 by adi-marc          #+#    #+#             */
/*   Updated: 2025/09/05 11:06:45 by adi-marc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int argc, char **argv)
{
    t_data  data;

    if (argc == 5 || argc == 6)
    {
        // Correct input check - DONE
        parse_input(&data, argv);
        // Populate data structures - DONE
        data_init(&data);
        // Start simulation with given data
        sim_start(&data);
        // Memory cleanup -> Either philos are full or a philo is dead
        //clean_data(&data);
    }
    else
        error_exit("Incorrect input");
}
