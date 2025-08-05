#include "../includes/push_swap.h"
#include <stdio.h>

// 스택의 상태를 출력해주는 유틸리티 함수
void print_stack(t_stack *stack, char name)
{
	t_node *current = stack->top;
	printf("Stack %c (size: %zu): ", name, get_stack_size(stack));
	while (current)
	{
		printf("%d ", current->data);
		current = current->next;
	}
	printf("\n");
}

int main(void)
{
	// 테스트용 스택 A와 B 생성
	t_stack *stack_a = create_stack();
	t_stack *stack_b = create_stack();

	// --------- 1단계: 푸시(push) 테스트 -----------
	printf("--- PUSH TEST ---\n");
	push(stack_a, 5);
	push(stack_a, 10);
	push(stack_a, 15);
	print_stack(stack_a, 'A'); // 출력: Stack A (size: 3): 15 10 5
	printf("Is stack A empty? %s\n", is_empty(stack_a) ? "Yes" : "No");
	printf("Top of stack A: %d\n\n", peek(stack_a));

	// --------- 2단계: 팝(pop) 테스트 -----------
	printf("--- POP TEST ---\n");
	pop(stack_a);
	print_stack(stack_a, 'A'); // 출력: Stack A (size: 2): 10 5
	pop(stack_a);
	print_stack(stack_a, 'A'); // 출력: Stack A (size: 1): 5
	printf("Top of the stack A: %d\n\n", peek(stack_a));

	// --------- 3단계: 엣지 케이스 테스트 -----------
	printf("--- EDGE CASE TEST (Single Node) ---\n");
	pop(stack_a); // 스택에 노드가 하나 남았을 때 pop
	print_stack(stack_a, 'A'); // 출력: Stack A (size: 0):

	printf("Is stack A empty? %s\n", is_empty(stack_a) ? "Yes" : "No");
	printf("--- EDGE CASE TEST (Empty Stack) ---\n");
	pop(stack_a); // 빈 스택에서 pop
	print_stack(stack_a, 'A'); // 출력: Stack A (size: 0):

	// --------- 4단계: 메모리 해제 테스트 -----------
	printf("\n--- FREE TEST ---\n");
	// 스택 A와 B에 메모리를 할당한 뒤 해제
	push(stack_a, 100);
	push(stack_b, 200);
	push(stack_b, 300);

	print_stack(stack_a, 'A');
	print_stack(stack_b, 'B');

	// free_stack 함수 호출
	free_stack(stack_a);
	free_stack(stack_b);

	printf("\nAll memory freed. Now checking with Valgrind...\n");

	return (0);
}