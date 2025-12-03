#include "n_queens.h"

/*
 * is_safe:
 *   현재까지 pos[0..col-1]에 놓인 퀸들과 (col,row)에 놓는 것이 충돌하는지 검사.
 *   같은 행이면 안 되고, 같은 대각선(행차 == 열차)도 안 된다.
 *   반환값: 1 -> 안전(놓아도 됨), 0 -> 충돌 발생(놓을 수 없음)
 */
int is_safe(const int *pos, int col, int row)
{
    int i;
    for (i = 0; i < col; ++i)
    {
        /* 같은 행 체크 */
        if (pos[i] == row)
            return 0;

        /* 대각선 체크: |pos[i] - row| == col - i 인 경우 충돌 */
        int diff = pos[i] - row;
        if (diff < 0)
            diff = -diff; /* abs 대신 수동 처리(허용 함수 목록에 abs 없음) */

        if (diff == (col - i))
            return 0;
    }
    return 1;
}

/*
 * print_solution:
 *   pos 배열에 저장된 한 해를 "p0 p1 p2 ... pn-1\n" 형식으로 출력한다.
 *   요구사항에 따라 각 열의 행 인덱스를 공백으로 구분하고 줄바꿈으로 끝낸다.
 */
void print_solution(const int *pos, int n)
{
    int i;
    for (i = 0; i < n; ++i)
    {
        if (i > 0)
            /* 숫자 사이에 공백 하나 삽입 */
            fprintf(stdout, " ");
        /* 각 칸의 행 인덱스를 출력 */
        fprintf(stdout, "%d", pos[i]);
    }
    /* 한 해의 끝은 개행 */
    fprintf(stdout, "\n");
}

/*
 * place_queens:
 *   col번째 열에 퀸을 놓는 모든 가능한 경우를 시도하는 재귀 함수.
 *   - col == n 이면 모든 열에 퀸을 놓은 것이므로 출력.
 *   - 각 row에 대해 is_safe 검사 후 재귀 호출(백트래킹).
 */
void place_queens(int *pos, int n, int col)
{
    int row;

    /* 모든 열에 배치가 끝나면 한 해를 출력 */
    if (col == n)
    {
        print_solution((const int *)pos, n);
        return;
    }

    /* 이번 열(col)에 가능한 모든 행(row)을 시도 */
    for (row = 0; row < n; ++row)
    {
        if (is_safe(pos, col, row))
        {
            pos[col] = row;            /* col열에 row를 배치 */
            place_queens(pos, n, col + 1); /* 다음 열로 진행 */
            /* 백트래킹: pos[col]은 다음 시도에서 덮어쓰기 되므로 별도 초기화 불필요 */
        }
    }
}

/*
 * main:
 *   인자 검사, 메모리 할당, 백트래킹 시작, 메모리 해제.
 *   - 인자 개수 != 2 또는 n <= 0 인 경우 간단히 에러 코드(1)로 종료.
 *   (문제 설명에서 음수는 테스트하지 않는다고 했으므로 간단 처리)
 */
int main(int argc, char **argv)
{
    int n;
    int *pos;

    if (argc != 2)
        return 1;

    n = atoi(argv[1]); /* atoi 사용 허용됨 */
    if (n <= 0)
        return 1;

    /* pos 배열 할당: 각 열에 어떤 행을 선택했는지 기록 */
    pos = (int *)calloc(n, sizeof(int));
    if (pos == NULL)
        return 1;

    /* 0번째 열부터 퀸 배치 시작 */
    place_queens(pos, n, 0);

    /* 할당 해제 후 종료 */
    free(pos);
    return 0;
}
