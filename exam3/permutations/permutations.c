/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jaeholee <makest@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 21:18:27 by Jaeholee          #+#    #+#             */
/*   Updated: 2025/08/02 21:18:28 by Jaeholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int ft_strlen(char *argv)
{
	int i = 0;
	while (argv[i])
		i++;
	return (i);
}

void swap(char *a, char *b)
{
	char tmp = *a;
	*a = *b;
	*b = tmp;
}

void insertsort(char *argv)
{
	int i = 0;
	int len = ft_strlen(argv);
	while (i < len)
	{
		int j = i + 1;
		while (j < len)
		{
			if (argv[i] > argv[j])
				swap(&argv[i], &argv[j]);
			j++;
		}
		i++;
	}
}

void move_char(char *string, int ind)
{
	char tmp = string[ind];
	while (ind)
	{
		string[ind] = string[ind - 1];
		ind--;
	}
	string[ind] = tmp;
}

void back_char(char *string, int ind)
{
	char tmp = string[0];
	int i = 0;
	while (i < ind)
	{
		string[i] = string[i + 1];
		i++;
	}
	string[ind] = tmp;
}


int dfs(char *string, int ind, char *buf)
{
	int len = ft_strlen(string);
	if (len <= 1)
	{
		buf[ind] = *string;
		puts((const char *)buf);
		buf[ind] = '\0';
		return (0);
	}
	int i = 0;
	while (string[i])
	{
		move_char(string, i);
		buf[ind] = *string;
		dfs(&string[1], ind + 1, buf);
		buf[ind] = '\0';
		back_char(string, i);
		i++;
	}
	return (0);
}

int main(int ac, char **argv)
{
	int len = ft_strlen(argv[1]);
	char *buf = calloc(sizeof(char), len + 2);
	if (!buf)
		return (1);
	insertsort(argv[1]);
	dfs(argv[1], 0, buf);
	free(buf);
}


























