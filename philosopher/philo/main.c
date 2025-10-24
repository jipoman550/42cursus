/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 12:59:18 by sisung            #+#    #+#             */
/*   Updated: 2025/10/24 12:01:42 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	t_data *data;

	if (argc != 5 && argc != 6)
		error_and_return(INVALID_ARGS, 1);

	data = init_data(argv, argc);
	if (!data)
		return (1);

	// 3. 시뮬레이션 시작
	// start_simulation(data);

	// 4. 자원 해제
	destroy_and_free(data);

	return (0);
}
