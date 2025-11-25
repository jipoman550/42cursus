/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 12:59:18 by sisung            #+#    #+#             */
/*   Updated: 2025/11/25 13:49:49 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 5 && argc != 6)
		return (error_and_return(INVALID_ARGS, 1));
	data = init_data(argv, argc);
	if (!data)
		return (1);
	if (start_simulation(data))
	{
		finalize_data(data);
		return (1);
	}
	finalize_data(data);
	return (0);
}
