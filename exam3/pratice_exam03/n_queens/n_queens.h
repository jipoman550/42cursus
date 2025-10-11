#ifndef N_QUEENS_H
#define N_QUEENS_H

/* 표준 입출력/메모리 함수 사용 */
#include <stdio.h>
#include <stdlib.h>

/* 함수 선언(프로토타입) */
int  is_safe(const int *pos, int col, int row);
/* 재귀적으로 퀸을 배치하는 함수 */
void place_queens(int *pos, int n, int col);
/* 현재 배치(pos, 길이 n)를 요구 형식으로 출력 */
void print_solution(const int *pos, int n);

#endif /* N_QUEENS_H */
