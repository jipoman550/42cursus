/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_queens.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jaeholee <makest@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:20:38 by Jaeholee          #+#    #+#             */
/*   Updated: 2025/08/03 18:20:39 by Jaeholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int print_queens(int chsize, char *buf)
{
	int i = 0;
	while (buf[i])
	{
		write(1, &buf[i], 1);
		i++;
		if (i < chsize)
			write(1, " ", 1);
		else
			write(1, "\n", 1);
	}
	return (0);
}

int set_check(int chsize, int i, int **check, int bufind, int setnum)
{
	check[0][i] = setnum;
	check[1][i + bufind] = setnum;
	check[2][(chsize - 1) - (bufind - i)] = setnum;
	return (0);
}

int check_check(int chsize, int i, int **check, int bufind)
{
	if (!check[0][i] && !check[1][i + bufind] && !check[2][(chsize - 1) - (bufind - i)])
		return (0);
	return (1);
}

int queens(int chsize, char *buf, int **check, int bufind)
{
	if (bufind == chsize)
	{
		print_queens(chsize, buf);
		return (0);
	}
	int i = 0;
	while (i < chsize)
	{
		if (check_check(chsize, i, check, bufind))
		{
			i++;
			continue ;
		}
		buf[bufind] = i + '0';
		set_check(chsize, i, check, bufind, 1);
		queens(chsize, buf, check, bufind + 1);
		set_check(chsize, i, check, bufind, 0);
		buf[bufind] = 0;
		i++;
	}
	return (0);
}

int main(int ac, char *argv[])
{
	if (ac != 2)
		return (1);
	int chsize = atoi(argv[1]);
	if (chsize <= 3)
	{
		write(1, "\n", 1);
		return (0);
	}
	char *buf = calloc(chsize + 1, sizeof(char));
	if (!buf)
		return (1);

	int **check = calloc(3, sizeof(int *));
	if (!check)
		return (1);
	check[0] = calloc(chsize, sizeof(int));
	if (!check[0])
		return (free(check), 1);
	check[1] = calloc((2 * chsize) - 1, sizeof(int));
	if (!check[1])
		return (free(check), free(check[0]), 1);
	check[2] = calloc((2 * chsize) - 1, sizeof(int));
	if (!check[2])
		return (free(check), free(check[0]), free(check[1]), 1);

	int bufind = 0;
	queens(chsize, buf, check, bufind);

	return (free(buf), free(check[0]), free(check[1]), free(check[2]), free(check), 0);
}





























