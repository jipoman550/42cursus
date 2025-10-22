/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 12:59:18 by sisung            #+#    #+#             */
/*   Updated: 2025/10/22 21:15:32 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h" // philo.h에는 <stdlib.h>, <stdbool.h> 등이 포함되어 있음

int main(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("Error: Invalid number of arguments.\n");
		return (1);
	}

	t_data *data;

	data = init_data(argv, argc);
	if (data == NULL)
		return (1);

	// 3. 시뮬레이션 시작 (다음 단계)
	// start_simulation(data);

	// 4. 자원 해제 (다음 단계)
	destroy_and_free(data);

	return (0);
}