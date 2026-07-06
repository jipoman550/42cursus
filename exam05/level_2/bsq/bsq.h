/**
 * @file bsq.h
 * @brief BSQ (Biggest Square Problem) 프로젝트의 헤더 파일.
 * @details 이 파일은 BSQ 문제를 해결하는 데 사용되는 주요 구조체와
 *          함수 프로토타입을 정의합니다.
 */
#ifndef BSQ_H
# define BSQ_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
/**
 * @struct s_map_info
 * @brief 지도의 메타데이터와 격자 데이터를 저장하는 구조체.
 *
 * @param lines 지도의 행 수.
 * @param width 지도의 열 수.
 * @param empty 빈 공간을 나타내는 문자.
 * @param obstacle 장애물을 나타내는 문자.
 * @param full 가장 큰 정사각형을 채울 문자.
 * @param grid 2차원 배열 형태의 지도 데이터.
 */
typedef struct s_map_info {
	int		lines;
	int		width;
	char	empty;
	char	obstacle;
	char	full;
	char	**grid;
}	t_map_info;

/**
 * @struct s_solution
 * @brief 찾은 가장 큰 정사각형의 정보를 저장하는 구조체.
 *
 * @param size 정사각형의 한 변의 길이.
 * @param y 정사각형의 우측 하단 꼭짓점의 y 좌표 (행).
 * @param x 정사각형의 우측 하단 꼭짓점의 x 좌표 (열).
 */
typedef struct s_solution {
	int		size;
	int		y;
	int		x;
}	t_solution;

/**
 * @brief 주어진 파일 스트림으로부터 맵을 처리합니다.
 * @param stream 맵 데이터가 포함된 파일 스트림 (e.g., stdin 또는 파일 포인터).
 * @return 성공 시 0, 에러 발생 시 1을 반환합니다.
 */
int			process_stream(FILE *stream);

/**
 * @brief 파일 스트림에서 맵을 읽고 유효성을 검사하여 t_map_info 구조체에 저장합니다.
 * @param stream 맵 데이터가 포함된 파일 스트림.
 * @return 성공 시 맵 정보가 담긴 t_map_info 포인터, 실패 시 NULL을 반환합니다.
 */
t_map_info	*read_map(FILE *stream);

/**
 * @brief 동적 계획법을 사용하여 지도에서 가장 큰 정사각형을 찾고 결과를 그립니다.
 * @param map 처리할 맵의 정보가 담긴 t_map_info 포인터.
 */
void		solve_bsq(t_map_info *map);

/**
 * @brief 해결된 맵을 표준 출력에 인쇄합니다.
 * @param map 출력할 맵의 정보가 담긴 t_map_info 포인터.
 */
void		print_map(t_map_info *map);

/**
 * @brief t_map_info 구조체와 관련된 모든 동적 할당 메모리를 해제합니다.
 * @param map 해제할 맵의 정보가 담긴 t_map_info 포인터.
 */
void		free_map(t_map_info *map);

/**
 * @brief 주어진 파일 디스크립터에 문자열을 출력합니다.
 * @param s 출력할 문자열.
 * @param fd 파일 디스크립터.
 */
void		ft_putstr_fd(char *s, int fd);

#endif