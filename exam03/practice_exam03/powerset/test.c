#include <stdio.h>
#include <stdlib.h>

// 결과를 출력하는 함수
void print_solution(int *tab, int len)
{
    int i = 0;
    while (i < len)
    {
        printf("%d", tab[i]);
        if (i < len - 1)
            printf(" ");
        i++;
    }
    printf("\n");
}

// 재귀적으로 부분 집합을 찾는 함수
// ac: 입력 배열의 전체 길이
// av: 입력 정수 배열 (파싱된 값들)
// target: 목표 합
// idx: 현재 검사 중인 입력 배열의 인덱스
// current_sum: 현재까지 선택된 원소들의 합
// buffer: 현재까지 선택된 원소들을 저장하는 임시 배열
// buf_idx: buffer에 저장된 원소의 개수
void solve(int ac, int *av, int target, int idx, int current_sum, int *buffer, int buf_idx)
{
    // 기저 조건(Base Case): 배열의 끝까지 탐색했을 때
    if (idx == ac)
    {
        if (current_sum == target)
            print_solution(buffer, buf_idx);
        return;
    }

    // 분기 1: 현재 숫자(av[idx])를 포함하는 경우
    // 버퍼에 현재 숫자를 담고, 합계에 더한 뒤 다음 인덱스로 넘어갑니다.
    buffer[buf_idx] = av[idx];
    solve(ac, av, target, idx + 1, current_sum + av[idx], buffer, buf_idx + 1);

    // 분기 2: 현재 숫자(av[idx])를 포함하지 않는 경우
    // 버퍼와 합계를 그대로 두고 다음 인덱스로만 넘어갑니다.
    solve(ac, av, target, idx + 1, current_sum, buffer, buf_idx);
}

int main(int argc, char **argv)
{
    // 인자가 없거나 숫자 집합이 없는 경우 처리 (문제 조건에 따라 유연하게 처리)
    if (argc < 2)
        return (0);

    int target = atoi(argv[1]); // 첫 번째 인자는 목표 합(n)
    int count = argc - 2;       // 집합 원소의 개수
    int *nums;                  // 파싱한 숫자를 담을 배열
    int *buffer;                // 재귀 탐색 중 선택된 숫자를 담을 버퍼
    int i;

    // 메모리 할당
    nums = malloc(sizeof(int) * count);
    buffer = malloc(sizeof(int) * count);
    if (!nums || !buffer)
        return (1); // malloc 에러 시 1 리턴

    // 문자열 인자를 정수 배열로 변환
    i = 0;
    while (i < count)
    {
        nums[i] = atoi(argv[i + 2]);
        i++;
    }

    // 재귀 함수 호출
    // 초기 상태: 인덱스 0, 합계 0, 버퍼 인덱스 0
    solve(count, nums, target, 0, 0, buffer, 0);

    // 메모리 해제
    free(nums);
    free(buffer);

    return (0);
}