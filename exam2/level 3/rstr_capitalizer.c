/*
공백을 기준으로 처리
*/

#include <unistd.h>

int is_space(char c)
{
	if (c >= 7 && c <= 13 || c == 32)
		return 1;
	return 0;
}

int main(int argc, char *argv[])
{
	if (argc <= 1)
	{
		write(1, "\n", 1);
		return 0;
	}

	int i = 1;
	while (i < argc)
	{
		int j = 0;
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] >= 'A' && argv[i][j] <= 'Z')
			{
				argv[i][j] += 32;
			}
			if ((argv[i][j] >= 'a' && argv[i][j] <= 'z') && (is_space(argv[i][j + 1]) || argv[i][j + 1] == '\0'))
			{
				argv[i][j] -= 32;
			}
			write(1, &argv[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}