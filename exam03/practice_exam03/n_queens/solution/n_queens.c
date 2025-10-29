#include "n_queens.h"

// 4. print_solution(pos, N)
void print_solution(const int *pos, int n)
{
	for (int i = 0; i < n; ++i)
	{
		if (i > 0)
			fprintf(stdout, " ");

		fprintf(stdout, "%d", pos[i]);
	}
	fprintf(stdout, "\n");
}

// 3. is_safe(pos, col, row)
int is_safe(const int *pos, int col, int row)
{
	for (int i = 0; i < col; ++i)
	{
		if (pos[i] == row)
			return 0;

		int diff = pos[i] - row;
		if (diff < 0)
			diff = -diff;

		if (diff == (col - i))
			return 0;
	}
	return 1;
}

// 2. place_queens(pos, N, col)
void place_queens(int *pos, int n, int col)
{
	if (col == n)
	{
		print_solution((const int *)pos, n);
		return;
	}

	for (int row = 0; row < n; ++row)
	{
		if (is_safe(pos, col, row))
		{
			pos[col] = row;
			place_queens(pos, n, col + 1);
		}
	}
}

// 1. main(argc, argv)
int main(int argc, char **argv)
{
	int n;
	int *pos;

	if (argc != 2)
		return 1;

	n = atoi(argv[1]);
	if (n <= 0)
		return 1;

	pos = (int *)calloc(n, sizeof(int));
	if (pos == NULL)
		return 1;

	place_queens(pos, n, 0);

	free(pos);
	return 0;
}
