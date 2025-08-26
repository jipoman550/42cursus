/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_sort_big.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:30:00 by sisung            #+#    #+#             */
/*   Updated: 2025/08/26 15:30:00 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <fcntl.h>

void init_stack(t_stack *stack)
{
	stack->top = NULL;
	stack->size = 0;
}

// Helper function to check if a stack is sorted by index
bool is_sorted_by_index(t_stack *stack)
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

// Helper function to check for duplicates in an array
bool is_duplicate(int *arr, int size, int value)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == value)
            return true;
    }
    return false;
}

// Helper function to generate an array of unique random integers
int *generate_random_unique_array(int size)
{
    int *arr = (int *)malloc(sizeof(int) * size);
    if (!arr)
        return NULL;

    for (int i = 0; i < size; i++)
    {
        int val;
        do {
            val = rand();
        } while (is_duplicate(arr, i, val));
        arr[i] = val;
    }
    return arr;
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

void run_radix_test(int size, int test_num)
{
    t_stack stack_a;
    t_stack stack_b;
    int *arr;

    arr = generate_random_unique_array(size);
    if (!arr)
    {
        printf("Test %d-%d: KO (Memory allocation failed)\n", size, test_num);
        return;
    }

    init_stack(&stack_a);
    init_stack(&stack_b);

    create_indexed_stack(&stack_a, arr, size);
    free(arr);

    fflush(stdout);
    int stdout_bk = dup(STDOUT_FILENO);
    int dev_null = open("/dev/null", O_WRONLY);
    dup2(dev_null, STDOUT_FILENO);
    close(dev_null);

    radix_sort(&stack_a, &stack_b);

    fflush(stdout);
    dup2(stdout_bk, STDOUT_FILENO);
    close(stdout_bk);

    if (is_sorted_by_index(&stack_a) && get_stack_size(&stack_b) == 0)
    {
        printf("Test %d-%d: OK\n", size, test_num);
    }
    else
    {
        printf("Test %d-%d: KO\n", size, test_num);
    }

    free_stack_nodes(&stack_a);
    free_stack_nodes(&stack_b);
}

int main(void)
{
    srand(time(NULL));

    printf("--- Testing Radix Sort (100 elements) ---\n");
    for (int i = 1; i <= 5; i++)
    {
        run_radix_test(100, i);
    }

    printf("\n--- Testing Radix Sort (500 elements) ---\n");
    for (int i = 1; i <= 5; i++)
    {
        run_radix_test(500, i);
    }

    return (0);
}
