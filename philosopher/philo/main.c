/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 12:59:18 by sisung            #+#    #+#             */
/*   Updated: 2025/10/23 07:35:39 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h" // philo.h에는 <stdlib.h>, <stdbool.h> 등이 포함되어 있음

int main(int argc, char **argv)
{
	t_data *data;

	if (argc != 5 && argc != 6)
	{
		printf("Error: Invalid number of arguments.\n");
		return (1);
	}

	data = init_data(argv, argc);
	if (!data)
		return (1);

	// 3. 시뮬레이션 시작
	// start_simulation(data);

	// 4. 자원 해제
	destroy_and_free(data);

	return (0);
}