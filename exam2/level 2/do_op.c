#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	if (argc == 4)
	{
		int i = 0;
		int s1 = atoi(argv[1]);
		int s2 = atoi(argv[3]);

		if (argv[2][0] == '+')
		{
			printf("%d", s1 + s2);
		}
		else if (argv[2][0] == '-')
		{
			printf("%d", s1 - s2);
		}
		else if (argv[2][0] == '*')
		{
			printf("%d", s1 * s2);
		}
		else if (argv[2][0] == '/')
		{
			printf("%d", s1 / s2);
		}
		else if (argv[2][0] == '%')
		{
			printf("%d", s1 % s2);
		}
		return 0;
	}
	printf("\n");
	return 0;
}