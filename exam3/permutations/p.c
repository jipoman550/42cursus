/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jaeholee <makest@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 16:17:34 by Jaeholee          #+#    #+#             */
/*   Updated: 2025/08/08 16:17:37 by Jaeholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int tmp_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return i;
}

int swap(char *a, char *b)
{
	char tmp = *a;
	*a = *b;
	*b = tmp;
	return (0);
}

int sorting(char *v, int num)
{
	int i = 0;
	while (i < num - 1)
	{
		int j = i + 1;
		while (j < num)
		{
			if (v[i] > v[j])
				swap(&v[i], &v[j]);
			j++;
		}
		i++;
	}
	return (0);
}

int dfs(char *v, int num, size_t visited, char *buf, int bufind)
{
	if (visited == (1UL << num) - 1)
	{
		puts(buf);
		return (0);
	}
	int i = -1;
	while (++i < num)
	{
		if (!((visited >> i) & 1))
		{
			buf[bufind] = v[i];
			dfs(v, num, visited | 1UL << i, buf, bufind + 1);
			//buf[bufind] = 0;
		}
	}
	return (0);
}

int main(int c, char *v[])
{
	(void)c;
	int num = tmp_strlen(v[1]);
	size_t visited = 0;
	sorting(v[1], num);
	char *buf = calloc(sizeof(char), num + 1);
	if (!buf)
		return (1);
	dfs(v[1], num, visited, buf, 0);
	return (0);
}





























