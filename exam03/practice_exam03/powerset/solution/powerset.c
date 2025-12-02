#include "powerset.h"

void print_solution(int *tab, int len)
{
	int i = 0;
	while (i < len)
	{
		printf("%d", tab[i]);
		if (i < len - 1)
			printf(" ");
		i++;
	}
	printf("\n");
}

void solve(int cnt, int *nums, int target, int idx, int current_sum, int *buffer, int buf_idx)
{
	if (idx == cnt)
	{
		if (current_sum == target)
			print_solution(buffer, buf_idx);
		return ;
	}

	buffer[buf_idx] = nums[idx];
	solve(cnt, nums, target, idx + 1, current_sum + nums[idx], buffer, buf_idx + 1);
	solve(cnt, nums, target, idx + 1, current_sum, buffer, buf_idx);
}

int main(int argc, char **argv)
{
	if (argc < 2)
		return (0);

	int target = atoi(argv[1]);
	int cnt = argc - 2;

	int *nums = malloc(sizeof(int) * cnt);
	int *buffer = malloc(sizeof(int) * cnt);

	if (!nums || !buffer)
		return (1);

	int i = 0;
	while (i < cnt)
	{
		nums[i] = atoi(argv[i + 2]);
		i++;
	}

	solve(cnt, nums, target, 0, 0, buffer, 0);

	free(nums);
	free(buffer);
	return (0);
}
