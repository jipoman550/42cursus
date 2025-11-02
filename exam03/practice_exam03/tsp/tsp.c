#include "tsp.h"

// 최대 도시 개수 (N <= 11)
#define MAX_CITIES 11

// 도시의 좌표를 저장하는 구조체
typedef struct {
	float x;
	float y;
} City;

// 도시 쌍 간의 거리를 저장할 배열
float distances[MAX_CITIES][MAX_CITIES];

// 전역 변수로 최단 경로 길이를 저장 (DFS를 통해 갱신됨)
float min_tour_length = FLT_MAX;

/**
 * @brief 두 도시 사이의 유클리드 거리를 계산합니다.
 */
float calc_distance(City a, City b) {
	float dx = b.x - a.x;
	float dy = b.y - a.y;
	return sqrtf(dx * dx + dy * dy);
}

/**
 * @brief 모든 도시 쌍 사이의 거리를 미리 계산합니다.
 */
void precalculate_distances(const City *cities, int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			distances[i][j] = calc_distance(cities[i], cities[j]);
		}
	}
}

/**
 * @brief 완전 탐색(DFS)을 통해 모든 경로를 탐색하고 최단 경로를 찾습니다.
 * @param current_city 현재 위치한 도시의 인덱스
 * @param visited_mask 현재까지 방문한 도시들을 기록한 비트마스크
 * @param current_path_length 현재까지 이동한 경로의 총 길이
 * @param N 도시의 총 개수
 */
void find_shortest_path(int current_city, int visited_mask, float current_path_length, int N) {
	// 1. (가지치기) 현재 경로가 이미 찾은 최단 경로보다 길다면, 이 경로는 답이 될 수 없으므로 탐색 중단
	if (current_path_length >= min_tour_length) {
		return;
	}

	// 2. (종료 조건) 모든 도시를 다 방문했는지 확인 (모든 비트가 1)
	if (visited_mask == (1 << N) - 1) {
		// 마지막 도시에서 출발 도시(0번)로 돌아오는 거리를 더합니다.
		float total_tour = current_path_length + distances[current_city][0];

		// 최단 경로 갱신
		if (total_tour < min_tour_length) {
			min_tour_length = total_tour;
		}
		return;
	}

	// 3. (재귀 단계) 아직 방문하지 않은 모든 도시를 다음 목적지로 시도
	for (int next_city = 0; next_city < N; next_city++) {
		// next_city가 아직 방문하지 않은 도시인지 확인 (비트마스크에 포함되어 있지 않음)
		if (!(visited_mask & (1 << next_city))) {

			// 다음 도시로 이동하며 재귀 호출
			find_shortest_path(
				next_city, // 다음 도시
				visited_mask | (1 << next_city), // 다음 도시를 포함시킨 새 마스크
				current_path_length + distances[current_city][next_city], // 경로 길이 누적
				N
			);
		}
	}
}

/**
 * @brief 메인 함수: 입력을 처리하고 TSP를 해결합니다.
 */
int main() {
	City cities[MAX_CITIES];
	int city_count = 0;
	float x, y;
	int result;

	// 표준 입력에서 좌표를 읽습니다.
	while (city_count < MAX_CITIES &&
		   (result = fscanf(stdin, "%f, %f\n", &x, &y)) == 2) {
		cities[city_count].x = x;
		cities[city_count].y = y;
		city_count++;
	}

	// 입력 처리 오류 검사
	if (result != EOF && result != 2) {
		fprintf(stderr, "Error: Invalid input format.\n");
		return 1;
	}

	// 도시가 1개 이하일 경우 (0개 또는 1개)
	if (city_count <= 1) {
		printf("%.2f\n", 0.0f);
		return 0;
	}

	// 1. 모든 도시 쌍 간의 거리 계산
	precalculate_distances(cities, city_count);

	// 2. 완전 탐색 시작:
	//    - 0번 도시에서 시작
	//    - 0번 도시만 방문했으므로 마스크는 1 << 0 (즉, 1)
	//    - 시작 길이는 0.0f
	find_shortest_path(0, 1, 0.0f, city_count);

	// 3. 결과 출력
	if (min_tour_length == FLT_MAX) {
		// 오류 처리 (이론적으로 발생하지 않음)
		fprintf(stderr, "Error: Path not found.\n");
		return 1;
	}

	printf("%.2f\n", min_tour_length);

	return 0;
}
