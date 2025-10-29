#include "n_queens.h"

// 4. print_solution(pos, N)
// 3. is_safe(pos, col, row)
// 2. place_queens(pos, N, col)
void place_queens(int *pos, int n, int col)
{
	int row;

	if (col == n)
	{
		print_solution((const int *)pos, n);
		return;
	}

	for (row = 0; row < n; ++row)
	{
		if (is_safe(pos, col, row))
		{
			pos[col] = row;
			place_queens(pos, n, col + 1)
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
