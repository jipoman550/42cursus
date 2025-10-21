/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 12:59:08 by sisung            #+#    #+#             */
/*   Updated: 2025/10/21 12:15:46 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int  parse_and_save_args(t_data *data, char **argv, int argc)
{
    long long	val;
    size_t		i;

    i = 1;
    while (i <= 4)
    {
        val = ft_parse_long(argv[i]);
        if (val == -1)
            return (-1);
        if (i == 1) data->num_of_philos = (size_t)val;
        else if (i == 2) data->time_to_die = val;
        else if (i == 3) data->time_to_eat = val;
        else if (i == 4) data->time_to_sleep = val;
        i++;
    }
    if (argc == 6)
    {
        val = ft_parse_long(argv[5]);
        if (val == -1)
        {
            printf("Error: Invalid argument value for must_eat_count.\n");
            return (-1);
        }
        data->must_eat_count = (size_t)val;
    }
    else
    {
        data->must_eat_count = 0;
    }
    return (0);
}

t_data *init_data(char **argv, int argc)
{
    t_data *    data;
    long long	val;
    size_t		i;

    data = (t_data *)malloc(sizeof(t_data));
    if (!data)
        return (NULL);

    if (parse_and_save_args(data, argv, argc) != 0)
    {
        free(data);
        printf("Error: Invalid argument value.\n");
        return (NULL);
    }

    if (init_forks(data) != 0)
    {
        free(data);
        return (NULL);
    }

    
    return (data);
}
