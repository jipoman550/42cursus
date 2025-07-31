#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stddef.h>
# include <limits.h> //INT_MIN, INT_MAX 사용 위해
# include <stdbool.h> // bool 타입 사용 위해
# include <stdlib.h> // malloc, free, exit 사용 위해
# include <unistd.h> // write 사용 위해
# include <stdio.h> // printf(test 용) 사용 위해

bool	is_validate_input(size_t tokens_count, char **tokens, int *arr);
char	**ft_split(char const *s, char c);
size_t	count_words(const char *s, char c);
char	**collect_tokens(int argc, char **argv, size_t *out_count);
void	ft_error();
void	free_all(char **strs, int *nums);
void	free_int_array(int *arr);
void	free_str_array(char **arr);

#endif
