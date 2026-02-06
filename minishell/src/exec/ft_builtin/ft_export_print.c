/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hama <hama@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 09:59:22 by hama              #+#    #+#             */
/*   Updated: 2026/02/05 19:34:02 by hama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "exec.h"

static int	cmp_env_key(char *a, char *b)
{
	size_t	len_a;
	size_t	len_b;
	size_t	min;
	int		result;

	len_a = key_len(a);
	len_b = key_len(b);
	if (len_a >= len_b)
		min = len_b;
	else
		min = len_a;
	result = ft_strncmp(a, b, min);
	if (result != 0)
		return (result);
	if (len_a != len_b)
	{
		if (len_a >= len_b)
			return (1);
		else
			return (-1);
	}
	return (0);
}

static void	put_escape(char *str)
{
	size_t	i;
	char	c;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		c = str[i];
		if (c == '\\' || c == '"')
			write(STDOUT_FILENO, "\\", 1);
		write(STDOUT_FILENO, &c, 1);
		i++;
	}
}

static void	print_declare_line(char *key_val)
{
	size_t	k_len;
	char	*val;

	k_len = key_len(key_val);
	write(STDOUT_FILENO, "declare -x ", 11);
	write(STDOUT_FILENO, key_val, k_len);
	if (key_val[k_len] == '=')
	{
		val = key_val + k_len + 1;
		write(STDOUT_FILENO, "=\"", 2);
		put_escape(val);
		write(STDOUT_FILENO, "\"", 1);
	}
	write(STDOUT_FILENO, "\n", 1);
}

static void	env_sort_print(char **arr, int n)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < n)
	{
		j = 0;
		while (j + 1 < n - i)
		{
			if (cmp_env_key(arr[j], arr[j + 1]) > 0)
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (arr[i])
		print_declare_line(arr[i++]);
}

int	export_print(char **envp)
{
	int		n;
	int		i;
	char	**arr;

	n = env_len(envp);
	arr = malloc(sizeof(char *) * (n + 1));
	if (!arr)
		return (1);
	i = 0;
	while (i < n)
	{
		arr[i] = envp[i];
		i++;
	}
	arr[n] = NULL;
	env_sort_print(arr, n);
	free(arr);
	return (0);
}
