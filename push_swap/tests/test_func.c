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

int main(void) {
	t_stack stack_a;
    t_stack stack_b;

    // 스택 초기화 stack_init 함수 뭐임? 처음봄.
    stack_init(&stack_a);
    stack_init(&stack_b);

    // 테스트 데이터 추가
    // 스택 A: 5 -> 4 -> 3 -> 2 -> 1 (top to bottom)
    push(&stack_a, 1);
    push(&stack_a, 2);
    push(&stack_a, 3);
    push(&stack_a, 4);
    push(&stack_a, 5);

    printf("--- Initial State ---\n");
    print_stack(&stack_a, 'A');
    print_stack(&stack_b, 'B');

    // 여기서부터 각 명령어 함수 테스트

    printf("\n--- Test: sa ---\n");
    sa(&stack_a); // 스택 A의 top 2개 (5, 4)가 바뀜
    print_stack(&stack_a, 'A'); // 예상 결과: Stack A: 4 5 3 2 1

    // 엣지 케이스 테스트 (스택 크기가 1일 때)
    printf("\n--- Test: sa with small stack ---\n");
    stack_free(&stack_a);
    stack_init(&stack_a);
    push(&stack_a, 10);
    sa(&stack_a); // size가 1이므로 아무 변화가 없어야 함
    print_stack(&stack_a, 'A'); // 예상 결과: Stack A: 10

    // ss 테스트 (a, b 스택이 모두 2개 이상일 때)
    printf("\n--- Test: ss ---\n");
    stack_free(&stack_a);
    stack_free(&stack_b);
    stack_init(&stack_a);
    stack_init(&stack_b);
    push(&stack_a, 20); push(&stack_a, 10); // A: 10 20
    push(&stack_b, 40); push(&stack_b, 30); // B: 30 40
    ss(&stack_a, &stack_b); // sa와 sb가 동시에 실행됨
    print_stack(&stack_a, 'A'); // 예상 결과: Stack A: 20 10
    print_stack(&stack_b, 'B'); // 예상 결과: Stack B: 40 30

	printf("\n--- Test: pb ---\n");
    stack_free(&stack_a);
    stack_free(&stack_b);
    stack_init(&stack_a);
    stack_init(&stack_b);
    push(&stack_a, 3);
    push(&stack_a, 2);
    push(&stack_a, 1); // A: 1 2 3

    pb(&stack_a, &stack_b); // stack_a의 1이 stack_b로 감
    print_stack(&stack_a, 'A'); // 예상 결과: Stack A: 2 3
    print_stack(&stack_b, 'B'); // 예상 결과: Stack B: 1

    printf("\n--- Test: pa ---\n");
    pa(&stack_a, &stack_b); // stack_b의 1이 다시 stack_a로 돌아감
    print_stack(&stack_a, 'A'); // 예상 결과: Stack A: 1 2 3
    print_stack(&stack_b, 'B'); // 예상 결과: Stack B: (empty)

	printf("\n--- Test: ra ---\n");
    stack_free(&stack_a);
    stack_init(&stack_a);
    push(&stack_a, 4);
    push(&stack_a, 3);
    push(&stack_a, 2);
    push(&stack_a, 1); // A: 1 2 3 4

    ra(&stack_a); // 맨 위 노드 1이 맨 아래로 이동
    print_stack(&stack_a, 'A'); // 예상 결과: Stack A: 2 3 4 1

    printf("\n--- Test: rr ---\n");
    stack_free(&stack_a);
    stack_free(&stack_b);
    stack_init(&stack_a);
    stack_init(&stack_b);
    push(&stack_a, 2); push(&stack_a, 1);
    push(&stack_b, 4); push(&stack_b, 3);
    rr(&stack_a, &stack_b);
    print_stack(&stack_a, 'A'); // 예상 결과: Stack A: 2 1
    print_stack(&stack_b, 'B'); // 예상 결과: Stack B: 4 3

	printf("\n--- Test: rra ---\n");
    stack_free(&stack_a);
    stack_init(&stack_a);
    push(&stack_a, 4);
    push(&stack_a, 3);
    push(&stack_a, 2);
    push(&stack_a, 1); // A: 1 2 3 4

    rra(&stack_a); // 맨 아래 노드 4가 맨 위로 이동
    print_stack(&stack_a, 'A'); // 예상 결과: Stack A: 4 1 2 3

    // 테스트 후 메모리 해제 stack_free 함수는 뭐임. 처음봄. 내가 구현해야하는 건가?
    stack_free(&stack_a);
    stack_free(&stack_b);
    return 0;
}
