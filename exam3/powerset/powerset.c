/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jaeholee <makest@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:55:51 by Jaeholee          #+#    #+#             */
/*   Updated: 2025/08/04 15:55:52 by Jaeholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int boxsum(char **buf)
{
	int sum = 0;
	int i = 0;
	while (buf[i])
	{
		sum += atoi(buf[i]);
		i++;
	}
	return (sum);
}

int printbuf(char **buf)
{
	int i = 0;
	while (buf[i])
	{
		printf("%s", buf[i]);
		i++;
		if (buf[i])
			printf(" ");
	}
	printf("\n");
	return (0);
}

int dfs(char **numbox, char **buf, int cmpnum, int boxsize, int bufind, int ind)
{
	if (cmpnum == boxsum(buf))
		printbuf(buf);
	if (ind > boxsize)
		return (0);
	int i = ind;
	while (i < boxsize)
	{
		buf[bufind] = numbox[i];
		dfs(numbox, buf, cmpnum, boxsize, bufind + 1, i + 1);
		buf[bufind] = 0;
		i++;
	}
	return (0);
}

int main(int argc, char **argv)
{
	int boxsize = argc - 2;
	int cmpnum = atoi(argv[1]);
	char **numbox = &argv[2];
	char **buf = calloc(sizeof(char *), argc - 1);
	if (!buf)
		return (1);
	dfs(numbox, buf, cmpnum, boxsize, 0, 0);
	return (free(buf), 0);
}
