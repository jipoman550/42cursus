#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h> // FLT_MAX를 사용하기 위해 필요

// 최대 도시 개수는 문제에서 11개로 제한됨
#define MAX_CITIES 11

// 도시의 좌표를 저장할 구조체 정의
typedef struct {
    float x;
    float y;
} Point;

// 전역 변수로 데이터 관리 (재귀 함수에서 접근하기 쉽게 하기 위함)
Point cities[MAX_CITIES];
int visited[MAX_CITIES]; // 방문 여부를 체크하는 배열 (1: 방문함, 0: 방문안함)
int n = 0; // 입력받은 도시의 실제 개수
float min_path = FLT_MAX; // 현재까지 발견한 최단 경로의 길이 (초기값은 아주 큰 수)

// 두 도시(인덱스 i, j) 사이의 거리를 구하는 함수
// 피타고라스 정리를 이용: sqrt((x2-x1)^2 + (y2-y1)^2)
float get_distance(int i, int j) {
    float dx = cities[i].x - cities[j].x;
    float dy = cities[i].y - cities[j].y;
    return sqrtf(dx * dx + dy * dy);
}

// 백트래킹(재귀) 함수: 현재 도시에서 시작하여 남은 도시들을 방문
// current_idx: 현재 있는 도시의 인덱스
// count: 지금까지 방문한 도시의 개수
// current_dist: 지금까지 이동한 거리의 합
void solve_tsp(int current_idx, int count, float current_dist) {

    // 가지치기 (Pruning):
    // 현재까지 온 거리가 이미 우리가 알고 있는 '최단 거리(min_path)'보다 길다면
    // 더 이상 탐색할 필요가 없습니다. (최단 경로가 될 수 없으므로)
    if (current_dist >= min_path) {
        return;
    }

    // 종료 조건 (Base Case):
    // 모든 도시를 다 방문했을 때 (count == n)
    if (count == n) {
        // 마지막 도시에서 다시 '시작 도시(0번)'로 돌아가는 거리를 더해야 함 (Closed Curve)
        float return_dist = get_distance(current_idx, 0);
        float total_dist = current_dist + return_dist;

        // 이번에 찾은 경로가 기존 최단 경로보다 짧다면 갱신
        if (total_dist < min_path) {
            min_path = total_dist;
        }
        return;
    }

    // 재귀 단계 (Recursive Step):
    // 모든 도시를 순회하며 다음 방문할 도시를 찾음
    for (int i = 0; i < n; i++) {
        // 아직 방문하지 않은 도시라면
        if (visited[i] == 0) {
            visited[i] = 1; // 방문 체크

            // 다음 도시로 이동 (count 1 증가, 거리 누적)
            solve_tsp(i, count + 1, current_dist + get_distance(current_idx, i));

            visited[i] = 0; // 백트래킹: 다른 경로 탐색을 위해 방문 체크 해제
        }
    }
}

int main(void) {
    float x, y;

    // 1. 데이터 입력 받기
    // 표준 입력(stdin)에서 '실수, 실수' 형태로 끝까지 읽어들임
    // fscanf는 입력 형식에 맞는 데이터를 읽으면 읽은 항목의 개수를 반환함
    while (fscanf(stdin, "%f, %f", &x, &y) == 2) {
        if (n < MAX_CITIES) {
            cities[n].x = x;
            cities[n].y = y;
            n++;
        }
    }

    // 예외 처리: 도시가 없거나 1개인 경우 거리는 0
    if (n <= 1) {
        fprintf(stdout, "0.00\n");
        return 0;
    }

    // 2. 알고리즘 시작
    // 경로는 '닫힌 곡선(Closed Curve)'이므로 어디서 시작하든 전체 길이는 같습니다.
    // 따라서 편의상 0번 도시에서 시작한다고 고정합니다.
    visited[0] = 1; // 시작 도시 방문 처리

    // 0번 도시에서 시작, 방문한 도시 수 1개, 현재 거리 0.0
    solve_tsp(0, 1, 0.0);

    // 3. 결과 출력
    // 소수점 둘째 자리까지 출력
    fprintf(stdout, "%.2f\n", min_path);

    return 0;
}