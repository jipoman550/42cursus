#include <unistd.h>

int main(int argc, char* argv[])
{
	if (argc == 3)
	{
		int i, j;
		int lookup[256] = {};

		i = 0;
		while (argv[1][i])
		{
			if(lookup[(int)argv[1][i]] == 0)
			{
				j = 0;
				while (argv[2][j])
				{
					if (argv[1][i] == argv[2][j] && !lookup[(int)argv[2][j]])
					{
						lookup[(int)argv[2][j]] = 1;
						write(1, &argv[1][i], 1);
						break;
					}
					j++;
				}
			}
			i++;
		}
		return (0);
	}
	write(1, "\n", 1);
	return 0;
}