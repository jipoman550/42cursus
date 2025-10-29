#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if (argc == 4)
	{
		int i = 0;
		if (argv[2][1])
		{
			write(1, "\n", 1);
			return 0;
		}
		while (argv[1][i])
		{
			if (argv[1][i] == argv[2][0])
			{
				argv[1][i] = argv[3][0];
			}
			write(1, &argv[1][i], 1);
			i++;
		}
	}
	write(1, "\n", 1);
	return 0;
}