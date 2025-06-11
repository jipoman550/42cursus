#include <unistd.h>

int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		char *s = argv[1];

		int i = 0;
		while(s[i])
		{
			i++;
		}
		while (i--)
		{
			write(1, &s[i], 1);
		}
	}
	write(1, "\n", 1);
	return (0);
}