/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jaeholee <makest@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:59:29 by Jaeholee          #+#    #+#             */
/*   Updated: 2025/08/08 14:59:29 by Jaeholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void putu(unsigned v)
{
    char buf[10];
    int k = 0;
    do { 
    buf[k++] = (char)('0' + (v % 10)); 
    v /= 10; 
    } while (v);
    while (k--) write(1, &buf[k], 1);
}

int print_board(char * board)
{
    int i = -1;
    while (board[++i]) {
        if (i) write(1, " ", 1);
        unsigned val = (unsigned)(board[i] - '0'); // 0,1,2,...,10,11...
        putu(val);
    }
    write(1, "\n", 1);
    return (0);
}

int cmp_abs(int pre_row, int pre_col, int row, int col)
{
	int d_row = pre_row - row;
	int d_col = pre_col - col;
	if (d_row < 0)
		d_row *= -1;
	if (d_col < 0)
		d_col *= -1;
	return (d_row == d_col);
}

int check_board(char *board, int col)
{
	if (!col)
		return (1);
	int pre_col = -1;
	int row = board[col] - '0';
	while (++pre_col < col)
	{
		int pre_row = board[pre_col] - '0';
		if (pre_row == row)
			return (0);
		if (cmp_abs(pre_row, pre_col, row, col))
			return (0);
	}
	return (1);
}

int dfs(char *board, int num, int col)
{
	if (col == num)
	{
		print_board(board);
		return (0);
	}
	int i = -1;
	while (++i < num)
	{
		board[col] = i + '0';
		if (check_board(board, col))
			dfs(board, num, col + 1);
	}
	return (0);
}

int main(int c, char *v[])
{
	(void) c;
	//예외 처리 필요
	int num = atoi(v[1]);
	char *board = calloc(sizeof(char), num + 1);
	if (!board)
		return (1);
	dfs(board, num, 0);
	return (0);
}
