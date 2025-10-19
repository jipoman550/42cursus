/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 12:59:18 by sisung            #+#    #+#             */
/*   Updated: 2025/10/18 12:59:20 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h" // philo.h에는 <stdlib.h>, <stdbool.h> 등이 포함되어 있음

int main(int argc, char **argv)
{
    // 1. 인자의 개수 확인 (프로그램 이름 포함 5개 또는 6개)
    if (argc != 5 && argc != 6)
    {
        // 사용법 출력 또는 간단한 에러 메시지 출력
        printf("Error: Invalid number of arguments.\n");
        return (1); // 42 과제에서는 exit(1) 대신 return 1;을 main에서 사용해도 됨
    }

    // 2. 데이터 구조체 초기화 및 인자 파싱을 위해 함수 호출 (init.c로 연결)
    // 힙에 t_data 구조체를 할당하고 초기화해야 하므로 포인터로 넘겨줄 준비를 합니다.
    t_data *data;

    // init_data 함수에서 data 구조체를 malloc하고 파싱 및 초기화를 모두 처리하도록 설계
    data = init_data(argv, argc);

    if (data == NULL) // 초기화 또는 파싱 중 에러 발생
        return (1);

    // 3. 시뮬레이션 시작 (다음 단계)
    // start_simulation(data);

    // 4. 자원 해제 (다음 단계)
    // cleanup_and_free(data);

    return (0);
}