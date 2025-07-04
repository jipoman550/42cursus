/*
1. 우선 처음부터 인덱스에 해당하는 문자를 모두 소문자로 만들어줌.
2. 그 와중에 다음 문자가 공백이거나 끝('\0') + 소문자면 그 때 대문자로 만들어줌.
3. while문 계속 돌리면서 write로 찍어내셈.
*/

#include <unistd.h>

int is_space(char c)
{
	if (c >= 8 && c <= 13 || c == 32)
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