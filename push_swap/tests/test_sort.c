#include "push_swap.h"
#include <stdio.h>

// 스택의 상태를 출력해주는 유틸리티 함수
void print_stack(t_stack *stack, char name)
{
	t_node *current = stack->top;
	printf("Stack %c (size: %zu): ", name, stack->size);
	while (current)
	{
		printf("%d ", current->data);
		current = current->next;
	}
	printf("\n");
}

// t_stack 구조체를 초기화하는 함수
void stack_init(t_stack *stack)
{
	stack->top = NULL;
	stack->size = 0;
}

// 스택의 모든 노드와 구조체를 해제하는 함수
void stack_free(t_stack *stack)
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
    // stack 구조체 자체는 스택에 할당되어 있으므로 free하지 않음
}

int main()
{
	t_stack stack_a;
    int input_arr[] = {5, 9, 4, 2};
    size_t size = sizeof(input_arr) / sizeof(int);

    // 스택 초기화
    stack_init(&stack_a);

    printf("--- 입력 값: ");
    for (size_t i = 0; i < size; i++)
        printf("%d ", input_arr[i]);
    printf("---\n");

    // create_indexed_stack 함수 호출
    create_indexed_stack(&stack_a, input_arr, size);

    // 결과 검증
    printf("\n--- 인덱싱된 스택 상태 ---\n");
    printf("예상 결과: Stack A (size: 4): 2 3 1 0\n");
    printf("실제 결과: ");
    print_stack(&stack_a, 'A');

    // 스택 메모리 해제
    stack_free(&stack_a);

    return 0;
}