/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 12:59:08 by sisung            #+#    #+#             */
/*   Updated: 2025/10/18 12:59:11 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// 데이터 구조체를 초기화하고 인자를 파싱하는 함수
t_data *init_data(char **argv, int argc)
{
    t_data		*data;
    long long	val;
    size_t		i;

    // 1. t_data 구조체 메모리 할당
    data = (t_data *)malloc(sizeof(t_data));
    if (!data)
        return (NULL);

    // 2. 필수 인자 파싱 및 저장 (argv[1] ~ argv[4])
    i = 1;
    while (i <= 4)
    {
        val = ft_parse_long(argv[i]);
        if (val == -1) // 파싱 또는 유효성 검사 실패
        {
            free(data);
            printf("Error: Invalid argument value.\n");
            return (NULL);
        }

        // i 값에 따라 적절한 멤버에 저장
        if (i == 1) data->num_of_philos = (size_t)val;
        else if (i == 2) data->time_to_die = val;
        else if (i == 3) data->time_to_eat = val;
        else if (i == 4) data->time_to_sleep = val;
        i++;
    }

    // 3. 선택 인자 파싱 및 저장 (argv[5])
    if (argc == 6)
    {
        val = ft_parse_long(argv[5]);
        if (val == -1) // 여기서도 양수 확인 필요
        {
            free(data);
            printf("Error: Invalid argument value for must_eat_count.\n");
            return (NULL);
        }
        data->must_eat_count = (size_t)val;
    }
    else
    {
        // 인자가 없을 경우 0으로 설정하여 무한/무제한 식사를 의미
        data->must_eat_count = 0;
    }

    // 이 시점에서 data 구조체의 인자 필드는 모두 채워졌습니다.
    // 다음 단계(뮤텍스/철학자 배열 초기화)를 진행합니다.
    return (data);
}
