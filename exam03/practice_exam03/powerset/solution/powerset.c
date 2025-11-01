#include "powerset.h"

int g_target;
int *g_set;
int g_total_count;

void safe_write(const char *buf, size_t len)
{
	write(1, buf, len);
}

void print_subset(int *selected, int count)
{
	char buffer[20];
	int len;

	if (count == 0)
	{
		safe_write("\n", 1);
		return ;
	}

	for (int i = 0 ; i < count; i++)
	{
		int num = selected[i];
		int is_negative = 0;
		char *ptr = buffer + sizeof(buffer) - 1;
		*ptr = '\0';

		if (num == 0)
		{
			*(--ptr) = '0';
		}
		else
		{
			if (num < 0)
			{
				is_negative =  1;
				num = -num;
			}

			while (num > 0)
			{
				*(--ptr) = (num % 10) + '0';
				num /= 10;
			}

			if (is_negative)
			{
				*(--ptr) = '-';
			}
		}

		len = buffer + sizeof(buffer) - 1 - ptr;

		safe_write(ptr, len);

		if (i < count - 1)
			safe_write(" ", 1);
	}
	safe_write("\n", 1);
}

void find_subsets(int index, long long current_sum, int *selected, int sel_count)
{
	if (index >= g_total_count)
	{
		if (current_sum == g_target)
		{
			print_subset(selected, sel_count);
		}
		return ;
	}

	find_subsets(index + 1, current_sum, selected, sel_count);

	selected[sel_count] = g_set[index];
	find_subsets(index + 1, current_sum + g_set[index], selected, sel_count + 1);
}

int main(int argc, char **argv)
{
	if (argc < 2)
		return 0;

	g_target = atoi(argv[1]);
	g_total_count = argc - 2;

	g_set = (int *)malloc(sizeof(int) * g_total_count);
	if (!g_set)
		return 1;

	for (int i = 0; i < g_total_count; i++)
		g_set[i] = atoi(argv[i + 2]);

	int *selected = (int *)malloc(sizeof(int) * g_total_count);
	if (!selected)
	{
		free(g_set);
		return 1;
	}

	find_subsets(0, 0, selected, 0);

	free(selected);
	free(g_set);

	return 0;
}
