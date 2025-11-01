#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h> // FLT_MAX for representing infinity

// 최대 도시 개수 (문제에서 11개 이하라고 했으므로 11로 설정)
#define MAX_CITIES 11
// 최대 비트마스크 크기 (2^11 = 2048)
#define MAX_MASK (1 << MAX_CITIES)

// 도시의 좌표를 저장하는 구조체
typedef struct {
    float x;
    float y;
} City;

// 동적 계획법 테이블: DP[mask][i] =
// 0번 도시에서 출발하여 mask에 포함된 도시를 모두 방문하고,
// i번 도시에서 끝나는 최소 경로 길이
float dp[MAX_MASK][MAX_CITIES];

// 도시 쌍 간의 거리를 저장할 배열
float distances[MAX_CITIES][MAX_CITIES];

// 현재 로드된 도시의 개수
int city_count = 0;

/**
 * @brief 두 도시 사이의 유클리드 거리를 계산합니다.
 * @param a 첫 번째 도시
 * @param b 두 번째 도시
 * @return 두 도시 사이의 거리 (float)
 */
float calc_distance(City a, City b) {
    float dx = b.x - a.x;
    float dy = b.y - a.y;
    // sqrtf는 float형 sqrt 계산 함수입니다. (필요에 따라 -lm 컴파일 옵션 필요)
    return sqrtf(dx * dx + dy * dy);
}

/**
 * @brief 모든 도시 쌍 사이의 거리를 미리 계산하여 distances 배열에 저장합니다.
 * @param cities 도시 배열
 * @param N 도시의 개수
 */
void precalculate_distances(const City *cities, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) {
                distances[i][j] = 0.0f;
            } else {
                distances[i][j] = calc_distance(cities[i], cities[j]);
            }
        }
    }
}

/**
 * @brief Held-Karp 동적 계획법을 사용하여 TSP의 최단 경로 길이를 계산합니다.
 * @param N 도시의 개수
 * @return 최단 경로 길이
 */
float solve_tsp(int N) {
    // DP 테이블 초기화: FLT_MAX는 "무한대"를 의미합니다.
    for (int i = 0; i < (1 << N); i++) {
        for (int j = 0; j < N; j++) {
            dp[i][j] = FLT_MAX;
        }
    }

    // 1. 기저 사례: 0번 도시에서 시작 (mask = 1 << 0)
    // 0번 도시에서 0번 도시로 가는 거리는 0
    dp[1][0] = 0.0f;

    // 2. DP 전이: 모든 마스크를 순회
    // mask는 현재까지 방문한 도시들의 집합입니다.
    for (int mask = 1; mask < (1 << N); mask++) {
        for (int u = 0; u < N; u++) { // u: 현재 마스크에서 마지막으로 방문한 도시
            // 현재 도시 u가 mask에 포함되어 있는지 확인합니다.
            if ((mask & (1 << u)) && dp[mask][u] != FLT_MAX) {

                // v: 다음에 방문할 도시
                for (int v = 0; v < N; v++) {
                    // v가 이미 방문한 도시(mask에 포함)가 아닌지 확인합니다.
                    if (!(mask & (1 << v))) {

                        // next_mask: u에서 v로 이동했을 때의 새로운 마스크
                        int next_mask = mask | (1 << v);

                        // 새로운 경로 길이: (u까지의 최소 경로 길이) + (u에서 v로의 거리)
                        float new_path_length = dp[mask][u] + distances[u][v];

                        // v까지 가는 경로 중 최소 길이를 갱신합니다.
                        if (new_path_length < dp[next_mask][v]) {
                            dp[next_mask][v] = new_path_length;
                        }
                    }
                }
            }
        }
    }

    // 3. 최종 결과: 모든 도시를 방문한 후 0번 도시로 돌아오는 최단 경로 찾기
    float min_tour_length = FLT_MAX;
    int final_mask = (1 << N) - 1; // 모든 비트가 1인 마스크

    // 모든 도시 i (i != 0)를 마지막 도시로 하여, i에서 0번 도시로 돌아오는 경로를 더합니다.
    for (int i = 1; i < N; i++) {
        // i까지의 최소 경로가 존재하는 경우에만 계산합니다.
        if (dp[final_mask][i] != FLT_MAX) {
            float tour_length = dp[final_mask][i] + distances[i][0];
            if (tour_length < min_tour_length) {
                min_tour_length = tour_length;
            }
        }
    }

    return min_tour_length;
}

/**
 * @brief 메인 함수: 입력을 처리하고 TSP를 해결합니다.
 */
int main() {
    City cities[MAX_CITIES];
    city_count = 0;
    float x, y;
    int result;

    // 표준 입력에서 좌표를 읽습니다. (형식: "%f, %f\n")
    while (city_count < MAX_CITIES &&
           (result = fscanf(stdin, "%f, %f\n", &x, &y)) == 2) {
        cities[city_count].x = x;
        cities[city_count].y = y;
        city_count++;
    }

    // fscanf가 2가 아닌 다른 값을 반환했으나 EOF가 아닌 경우, 잘못된 입력 형식 오류를 stderr에 출력
    if (result != EOF && result != 2) {
        fprintf(stderr, "Error: Invalid input format.\n");
        return 1;
    }

    // 도시가 1개 미만일 경우 처리
    if (city_count < 1) {
        // 도시가 0개인 경우, 경로 길이는 0입니다.
        printf("%.2f\n", 0.0f);
        return 0;
    }

    // 도시가 1개일 경우, 0번 도시에서 시작해서 0번 도시로 돌아오는 경로의 길이는 0입니다.
    if (city_count == 1) {
        printf("%.2f\n", 0.0f);
        return 0;
    }

    // 1. 모든 도시 쌍 간의 거리 계산
    precalculate_distances(cities, city_count);

    // 2. TSP 해결
    float shortest_path_length = solve_tsp(city_count);

    // 3. 결과 출력 (%.2f 형식)
    if (shortest_path_length == FLT_MAX) {
        // 이 코드는 모든 도시가 연결되어 있지 않은 경우에 발생할 수 있지만,
        // 유클리드 거리에서는 모든 도시가 연결되어 있으므로 보통 발생하지 않습니다.
        fprintf(stderr, "Error: No valid path found.\n");
        return 1;
    }

    printf("%.2f\n", shortest_path_length);

    return 0;
}
