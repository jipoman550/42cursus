#include "push_swap.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h> // for time()
#include <stdlib.h> // for srand() and rand()
#include <fcntl.h>

// 유일한 정수 배열을 생성하는 도우미 함수
// 이 함수는 placeholder이며, 당신이 직접 구현해야 합니다.
int *generate_random_unique_array(int size)
{
    int *arr;
    bool *is_used;
    int i;
    int num;

    // 배열과 사용 여부 배열을 동적 할당
    arr = (int *)malloc(sizeof(int) * size);
    is_used = (bool *)calloc(1000, sizeof(bool)); // 1000은 임시 최대값입니다.

    if (!arr || !is_used)
    {
        free(arr);
        free(is_used);
        return NULL;
    }

    srand(time(NULL)); // 난수 시드 초기화

    i = 0;
    while (i < size)
    {
        num = rand() % 1000; // 0~999 사이의 랜덤 정수 생성
        if (!is_used[num])
        {
            arr[i] = num;
            is_used[num] = true;
            i++;
        }
    }

    free(is_used);
    return arr;
}

// 스택이 정렬되었는지 확인하는 간단한 유틸리티
bool is_sorted(t_stack *stack)
{
    t_node *current;

    // 스택 크기가 1 이하면 항상 정렬된 상태
    if (stack->size <= 1)
        return true;

    current = stack->top;
    while (current && current->next)
    {
        // 현재 노드의 인덱스가 다음 노드의 인덱스보다 크면 정렬되지 않음
        if (current->index > current->next->index)
            return false;
        current = current->next;
    }
    return true;
}

void free_stack_nodes(t_stack *stack)
{
    t_node  *current_node;
    t_node  *next_node;

    current_node = stack->top;
    while (current_node != NULL)
    {
        next_node = current_node->next;
        free(current_node);
        current_node = next_node;
    }
    stack->top = NULL;
    stack->size = 0;
}

void run_test(int size)
{
    int *arr;
    t_stack *stack_a;
    t_stack *stack_b;

    printf("--- 스택 크기 테스트: %d ---\n", size);

    // 초기 배열 생성 및 유효성 검사
    arr = generate_random_unique_array(size);
    if (!arr)
    {
        fprintf(stderr, "오류: 배열 생성 실패.\n");
        return;
    }

    // 스택 초기화
    stack_a = create_stack();
    create_indexed_stack(stack_a, arr, size);
    stack_b = create_stack();

	fflush(stdout);
    int stdout_bk = dup(STDOUT_FILENO);
    int dev_null = open("/dev/null", O_WRONLY);
    dup2(dev_null, STDOUT_FILENO);
    close(dev_null);

    // 정렬 알고리즘 실행
    run_sort(stack_a, stack_b);

	fflush(stdout);
    dup2(stdout_bk, STDOUT_FILENO);
    close(stdout_bk);

    // 스택 정렬 상태 확인
    if (is_sorted(stack_a))
        printf("결과: OK\n");
    else
        printf("결과: KO\n");

    // 메모리 정리
    free_stack_nodes(stack_a);
    free(stack_a);
    free(stack_b);
    free(arr);

    // generate 함수에서 tokens를 생성했다면, 그 또한 해제해야 합니다.
    printf("--- 크기 %d 테스트 완료 ---\n\n", size);
}

int main(void)
{
    // 작은 스택 크기 테스트
    run_test(1);
    run_test(2);
    run_test(3);
    run_test(4);
    run_test(5);

    // 큰 스택 크기 테스트
    run_test(100);
    run_test(500);

    return (0);
}