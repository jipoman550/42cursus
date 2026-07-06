/**
 * @file bsq.c
 * @brief BSQ (Biggest Square Problem) 프로젝트의 메인 소스 파일.
 * @details 지도 파일 또는 표준 입력으로부터 맵을 읽어 가장 큰 정사각형을 찾아 출력합니다.
 */
#include "bsq.h"

/**
 * @brief 파일 디스크립터에 문자열을 쓴다.
 * @param s 쓸 문자열.
 * @param fd 대상 파일 디스크립터.
 */
void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
		write(fd, s++, 1);
}

/**
 * @brief "map error" 메시지를 표준 에러(stderr)에 출력한다.
 * @return 항상 1을 반환하여 에러 상태를 나타낸다.
 */
static int	display_error(void)
{
	ft_putstr_fd("map error\n", 2);
	return (1);
}

/**
 * @brief 프로그램의 주 진입점.
 * @param argc 커맨드 라인 인자의 수.
 * @param argv 커맨드 라인 인자 배열.
 * @return 성공 시 0.
 */
int	main(int argc, char **argv)
{
	int		i;
	FILE	*file;

	if (argc == 1)
	{
		// 인자가 없으면 표준 입력을 처리한다.
		if (process_stream(stdin) != 0)
			display_error();
	}
	else
	{
		i = 1;
		// 각 파일 인자를 순회하며 처리한다.
		while (i < argc)
		{
			file = fopen(argv[i], "r");
			if (file == NULL)
				display_error();
			else
			{
				if (process_stream(file) != 0)
					display_error();
				fclose(file);
			}
			i++;
		}
	}
	return (0);
}

/**
 * @brief 단일 파일 스트림을 처리하여 BSQ 문제를 해결한다.
 * @param stream 처리할 맵이 포함된 파일 스트림.
 * @return 성공 시 0, 에러 발생 시 1.
 */
int	process_stream(FILE *stream)
{
	t_map_info	*map;

	// 맵을 읽고 유효성을 검사한다.
	map = read_map(stream);
	if (map == NULL)
		return (1);
	// BSQ 문제를 푼다.
	solve_bsq(map);
	// 결과를 출력한다.
	print_map(map);
	// 할당된 메모리를 해제한다.
	free_map(map);
	return (0);
}

/**
 * @brief 문자열을 정수로 변환한다 (기본적인 atoi 구현).
 * @param str 변환할 숫자 문자열.
 * @return 변환된 정수.
 */
static int	ft_atoi(const char *str)
{
	int	res;

	res = 0;
	while (*str >= '0' && *str <= '9')
		res = res * 10 + (*str++ - '0');
	return (res);
}

/**
 * @brief 맵의 첫 번째 라인(메타 정보)을 파싱한다.
 * @param map 메타 정보를 저장할 t_map_info 구조체 포인터.
 * @param line 파싱할 첫 번째 라인 문자열.
 * @param len 라인의 길이.
 * @return 파싱 및 유효성 검사 성공 시 1, 실패 시 0.
 */
static int	parse_meta(t_map_info *map, char *line, ssize_t len)
{
	if (len < 5)
		return (0);
	line[len - 1] = '\0';
	map->full = line[len - 2];
	map->obstacle = line[len - 3];
	map->empty = line[len - 4];
	line[len - 4] = '\0';
	map->lines = ft_atoi(line);
	if (map->lines <= 0 || (map->empty == map->obstacle)
		|| (map->empty == map->full) || (map->obstacle == map->full))
		return (0);
	return (1);
}

/**
 * @brief 맵의 격자(grid) 부분을 읽고 유효성을 검사한다.
 * @param map 격자 정보를 저장할 t_map_info 구조체 포인터.
 * @param stream 맵 데이터가 포함된 파일 스트림.
 * @return 읽기 및 유효성 검사 성공 시 1, 실패 시 0.
 */
static int	read_grid(t_map_info *map, FILE *stream)
{
	char	*line;
	size_t	cap;
	ssize_t	len;
	int		i;

	i = 0;
	line = NULL;
	cap = 0;
	while (i < map->lines)
	{
		// 한 줄을 읽는다. 파일 끝에 도달하거나 개행 문자가 없으면 에러.
		if ((len = getline(&line, &cap, stream)) <= 0 || line[len - 1] != '\n')
		{
			free(line);
			return (0);
		}
		line[len - 1] = '\0';
		// 첫 번째 줄의 길이를 맵의 너비로 설정한다.
		if (i == 0)
			map->width = len - 1;
		// 모든 줄의 길이가 동일한지, 맵의 너비가 0이 아닌지 확인한다.
		if (map->width != (int)(len - 1) || (map->lines > 0 && map->width == 0))
		{
			free(line);
			return (0);
		}
		// getline으로 할당된 버퍼의 소유권을 map->grid[i]로 이전한다.
		map->grid[i++] = line;
		// 다음 getline 호출 시 새로운 버퍼를 할당받도록 line을 NULL로 설정한다.
		line = NULL;
	}
	return (1);
}

/**
 * @brief 파일 스트림에서 전체 맵을 읽어 t_map_info 구조체를 생성하고 반환한다.
 * @param stream 맵 데이터가 포함된 파일 스트림.
 * @return 성공 시 완전히 파싱된 t_map_info 구조체 포인터,
 *         실패(메모리 할당, 파일 형식 오류 등) 시 NULL.
 */
t_map_info	*read_map(FILE *stream)
{
	t_map_info	*map;
	char		*line;
	size_t		cap;
	ssize_t		len;

	// 맵 정보 구조체 메모리 할당.
	map = calloc(1, sizeof(t_map_info));
	if (!map)
		return (NULL);
	line = NULL;
	cap = 0;
	// 첫 줄(메타 정보)을 읽고 파싱한다.
	if ((len = getline(&line, &cap, stream)) <= 0 || !parse_meta(map, line, len))
	{
		free(map);
		free(line);
		return (NULL);
	}
	free(line);
	// 격자를 저장할 포인터 배열을 할당한다.
	map->grid = malloc(sizeof(char *) * map->lines);
	if (!map->grid || !read_grid(map, stream))
	{
		// 격자 읽기 실패 시, 이미 할당된 메모리를 정리한다.
		map->lines = 0;
		free_map(map);
		return (NULL);
	}
	return (map);
}

/**
 * @brief 세 정수 중 가장 작은 값을 반환한다.
 * @param a 첫 번째 정수.
 * @param b 두 번째 정수.
 * @param c 세 번째 정수.
 * @return 세 정수 중 최소값.
 */
static int	min3(int a, int b, int c)
{
	if (b < a)
		a = b;
	if (c < a)
		a = c;
	return (a);
}

/**
 * @brief 찾은 가장 큰 정사각형을 맵에 그린다.
 * @param map 수정할 맵 정보 구조체 포인터.
 * @param sol 가장 큰 정사각형의 정보(위치, 크기).
 */
static void	draw_solution(t_map_info *map, t_solution *sol)
{
	int	i;
	int	j;

	i = sol->y - sol->size + 1;
	while (i <= sol->y)
	{
		j = sol->x - sol->size + 1;
		while (j <= sol->x)
		{
			map->grid[i][j] = map->full;
			j++;
		}
		i++;
	}
}

/**
 * @brief 동적 계획법(DP)을 사용하여 가장 큰 정사각형을 찾는다.
 * @details 공간 복잡도를 O(M)으로 최적화하기 위해 두 개의 행만 사용한다.
 * @param map 해결할 맵 정보 구조체 포인터.
 */
void	solve_bsq(t_map_info *map)
{
	int			*dp[2];
	t_solution	sol;
	int			i;
	int			j;

	// 맵이 비어있으면 아무것도 하지 않는다.
	if (map->lines == 0 || map->width == 0)
		return ;
	// 솔루션 구조체 초기화.
	sol = (t_solution){0, 0, 0};
	// DP 테이블로 사용할 두 개의 행을 할당한다.
	dp[0] = calloc(map->width, sizeof(int));
	dp[1] = calloc(map->width, sizeof(int));
	if (!dp[0] || !dp[1])
		return ;
	i = -1;
	// 맵을 한 줄씩 순회한다.
	while (++i < map->lines)
	{
		j = -1;
		// 현재 줄의 각 칸을 순회한다.
		while (++j < map->width)
		{
			// 현재 칸이 장애물이면, 이 칸을 우하단으로 하는 정사각형은 없다.
			if (map->grid[i][j] == map->obstacle)
				dp[i % 2][j] = 0;
			// 맵의 경계(첫 행 또는 첫 열)에 있으면, 정사각형 크기는 1이다.
			else if (i == 0 || j == 0)
				dp[i % 2][j] = 1;
			else
				// DP 점화식: 현재 칸의 값 = 1 + (왼쪽, 위, 왼쪽-위 대각선) 중 최소값.
				// (i % 2)는 현재 행, (i + 1) % 2는 이전 행을 가리킨다.
				dp[i % 2][j] = 1 + min3(dp[(i + 1) % 2][j], \
					dp[i % 2][j - 1], dp[(i + 1) % 2][j - 1]);
			// 현재까지 찾은 가장 큰 정사각형보다 더 큰 것을 찾으면 갱신한다.
			if (dp[i % 2][j] > sol.size)
				sol = (t_solution){dp[i % 2][j], i, j};
		}
	}
	// 찾은 솔루션을 맵에 그린다.
	draw_solution(map, &sol);
	// DP 테이블 메모리 해제.
	free(dp[0]);
	free(dp[1]);
}

/**
 * @brief 최종 맵을 표준 출력(stdout)에 출력한다.
 * @param map 출력할 맵 정보 구조체 포인터.
 */
void	print_map(t_map_info *map)
{
	int	i;

	i = 0;
	while (i < map->lines)
	{
		ft_putstr_fd(map->grid[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}

/**
 * @brief 맵 구조체와 관련된 모든 동적 할당 메모리를 해제한다.
 * @param map 해제할 맵 정보 구조체 포인터.
 */
void	free_map(t_map_info *map)
{
	int	i;

	if (!map)
		return ;
	if (map->grid)
	{
		i = 0;
		// 각 줄에 대해 할당된 메모리를 해제한다.
		while (i < map->lines && map->grid[i])
		{
			free(map->grid[i]);
			i++;
		}
		free(map->grid);
	}
	free(map);
}