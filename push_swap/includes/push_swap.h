/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 18:18:56 by sisung            #+#    #+#             */
/*   Updated: 2025/08/06 20:50:20 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stddef.h>
# include <limits.h> //INT_MIN, INT_MAX 사용 위해
# include <stdbool.h> // bool 타입 사용 위해
# include <stdlib.h> // malloc, free, exit 사용 위해
# include <unistd.h> // write 사용 위해

typedef struct s_node
{
	int				data;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_stack
{
	t_node	*top;
	size_t	size;
}	t_stack;

bool	is_validate_input(size_t tokens_count, char **tokens, int *arr);
char	**ft_split(char const *s, char c);
size_t	count_words(const char *s, char c);
char	**collect_tokens(int argc, char **argv, size_t *out_count);

void	ft_error(void);
void	free_all(char **strs, int *nums);
void	free_int_array(int *arr);
void	free_str_array(char **arr);

t_node	*new_node(int data);
t_stack	*create_stack(void);
void	free_stack(t_stack *stack);

void	create_indexed_stack(t_stack *stack_a, int *input_arr, int size);

void	push(t_stack *stack, int data);
int		pop(t_stack *stack);

int		peek(t_stack *stack);
bool	is_empty(t_stack *stack);
size_t	get_stack_size(t_stack *stack);

void	sa(t_stack *stack_a);
void	sb(t_stack *stack_b);
void	ss(t_stack *stack_a, t_stack *stack_b);

void	pa(t_stack *stack_a, t_stack *stack_b);
void	pb(t_stack *stack_b, t_stack *stack_a);

void	ra(t_stack *stack_a);
void	rb(t_stack *stack_b);
void	rr(t_stack *stack_a, t_stack *stack_b);

void	rra(t_stack *stack_a);
void	rrb(t_stack *stack_b);
void	rrr(t_stack *stack_a, t_stack *stack_b);

#endif
