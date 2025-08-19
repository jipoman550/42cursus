#include "push_swap.h"
#include <stdio.h>
#include <stdbool.h>

// 스택의 상태를 출력해주는 유틸리티 함수
void print_stack(t_stack *stack, char name)
{
	t_node *current = stack->top;
	printf("Stack %c (size: %zu): ", name, get_stack_size(stack));
	while (current)
	{
		printf("%d(idx:%zu) ", current->data, current->index);
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
    stack->top = NULL;
    stack->size = 0;
}

// Helper function to check if a stack is sorted by index
bool is_sorted(t_stack *stack)
{
    t_node *current;

    if (get_stack_size(stack) <= 1)
        return true;
    current = stack->top;
    while (current && current->next)
    {
        if (current->index > current->next->index)
            return false;
        current = current->next;
    }
    return true;
}

void run_test(const char *test_name, int *input_arr, size_t size)
{
    t_stack stack_a;
    t_stack stack_b;

    stack_init(&stack_a);
    stack_init(&stack_b);

    printf("\n--- Test Case: %s (Size: %zu) ---\n", test_name, size);
    printf("Input Array: ");
    for (size_t i = 0; i < size; i++)
        printf("%d ", input_arr[i]);
    printf("\n");

    create_indexed_stack(&stack_a, input_arr, size);
    printf("Initial State: ");
    print_stack(&stack_a, 'A');

    sort_small(&stack_a, &stack_b);

    printf("Final State:   ");
    print_stack(&stack_a, 'A');
    printf("Stack B (should be empty): ");
    print_stack(&stack_b, 'B');

    if (is_sorted(&stack_a) && get_stack_size(&stack_b) == 0)
        printf("Result: PASSED\n");
    else
        printf("Result: FAILED\n");

    stack_free(&stack_a);
    stack_free(&stack_b);
}

int main()
{
    // Test cases for sort_2
    int arr2_1[] = {1, 0}; run_test("sort_2 - Unsorted", arr2_1, 2);
    int arr2_2[] = {0, 1}; run_test("sort_2 - Sorted", arr2_2, 2);

    // Test cases for sort_3
    int arr3_1[] = {2, 1, 0}; run_test("sort_3 - 2 1 0", arr3_1, 3);
    int arr3_2[] = {0, 2, 1}; run_test("sort_3 - 0 2 1", arr3_2, 3);
    int arr3_3[] = {1, 0, 2}; run_test("sort_3 - 1 0 2", arr3_3, 3);
    int arr3_4[] = {1, 2, 0}; run_test("sort_3 - 1 2 0", arr3_4, 3);
    int arr3_5[] = {2, 0, 1}; run_test("sort_3 - 2 0 1", arr3_5, 3);
    int arr3_6[] = {0, 1, 2}; run_test("sort_3 - Sorted", arr3_6, 3);

    // Test cases for sort_4
    int arr4_1[] = {3, 2, 1, 0}; run_test("sort_4 - Unsorted", arr4_1, 4);
    int arr4_2[] = {0, 3, 2, 1}; run_test("sort_4 - 0 at top", arr4_2, 4);
    int arr4_3[] = {1, 0, 3, 2}; run_test("sort_4 - 0 second", arr4_3, 4);
    int arr4_4[] = {2, 3, 0, 1}; run_test("sort_4 - 0 third", arr4_4, 4);
    int arr4_5[] = {3, 2, 0, 1}; run_test("sort_4 - 0 fourth", arr4_5, 4);
    int arr4_6[] = {0, 1, 2, 3}; run_test("sort_4 - Sorted", arr4_6, 4);

    // Test cases for sort_5
    int arr5_1[] = {4, 3, 2, 1, 0}; run_test("sort_5 - Unsorted", arr5_1, 5);
    int arr5_2[] = {0, 4, 3, 2, 1}; run_test("sort_5 - 0 at top", arr5_2, 5);
    int arr5_3[] = {1, 0, 4, 3, 2}; run_test("sort_5 - 0 second", arr5_3, 5);
    int arr5_4[] = {2, 1, 0, 4, 3}; run_test("sort_5 - 0 third", arr5_4, 5);
    int arr5_5[] = {3, 2, 1, 0, 4}; run_test("sort_5 - 0 fourth", arr5_5, 5);
    int arr5_6[] = {4, 3, 2, 0, 1}; run_test("sort_5 - 0 fifth", arr5_6, 5);
    int arr5_7[] = {0, 1, 2, 3, 4}; run_test("sort_5 - Sorted", arr5_7, 5);

    return 0;
}
