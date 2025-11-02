#include "tsp.h"

// 최대 도시 개수
#define MAX_CITIES 11

// 도시의 좌표를 저장하는 구조체
typedef struct {
	float x;
	float y;
} City;

// 도시 쌍 간의 거리를 저장할 배열
float distances[MAX_CITIES][MAX_CITIES];

// 전역 변수로 최단 경로 길이를 저장 (DFS로 갱신됨)
float min_tour_length = FLT_MAX;

float calc_distance(City a, City b)
{
	float dx = b.x - a.x;
	float dy = b.y - a.y;
	return sqrtf(dx * dx + dy * dy);
}

void	precalculate_distances(const City *cities, int N)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			distances[i][j] = calc_distance(cities[i], cities[j]);
		}
	}
}

void	find_shortest_path(int current_city, int visited_mask, float current_path_length, int N)
{
	// 1. (가지치기) 현재 경로가 이미 찾은 최단 경로보다 길면, 이 경로는 답이 아님 -> 탐색 중단
	if (current_path_length >= min_tour_length)
		return ;

	// 2. (종료 조건) 모든 도시를 다 방문했는지 확인 (모든 비트가 1)
	if (visited_mask == (1 << N) - 1)
	{
		// 마지막 도시에서 출발 도시(0번)로 돌아오는 거리를 더하기
		float total_tour = current_path_length + distances[current_city][0];

		// 최단 경로 갱신
		if (total_tour < min_tour_length)
			min_tour_length = total_tour;
		return ;
	}

	// 3. (재귀 단계) 아직 방문하지 않은 모든 도시를 다음 목적지로 시도
	for (int next_city = 0; next_city < N; next_city++)
	{
		if (!(visited_mask & (1 << next_city)))
		{
			find_shortest_path(
				next_city,
				visited_mask | (1 << next_city),
				current_path_length + distances[current_city][next_city],
				N
			);
		}
	}
}

int	main()
{
	City cities[MAX_CITIES];
	int city_count = 0;
	float x, y;
	int result;

	// 표준 입력에서 좌표를 읽기
	while (city_count < MAX_CITIES && (result = fscanf(stdin, "%f, %f\n", &x, &y)) == 2)
	{
		cities[city_count].x = x;
		cities[city_count].y = y;
		city_count++;
	}

	// 입력 처리 오류 검사
	if (result != EOF && result != 2)
	{
		fprintf(stderr, "Error: Invalid input format.\n");
		return 1;
	}

	// 도시가 1개 이하일 경우 (0개 또는 1개)
	if (city_count <= 1)
	{
		fprintf(stdout, "%.2f\n", 0.0f);
		return 0;
	}

	// 1. 모든 도시 쌍 간의 거리 계산
	precalculate_distances(cities, city_count);

	// 2. 완전 탐색 시작
	find_shortest_path(0, 1, 0.0f, city_count);

	// 3. 결과 출력
	if (min_tour_length == FLT_MAX)
	{
		fprintf(stderr, "Error: Path not found.\n");
		return 1;
	}

	fprintf(stdout, "%.2f\n", min_tour_length);

	return 0;
}
