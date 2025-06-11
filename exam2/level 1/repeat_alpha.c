#include <unistd.h>

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		write(1, "\n", 1);
		return (0);
	}
	char	asd;

	char *s = argv[1];

	if (s[0] == '\0')
	{
		write(1, "\n", 1);
		return (0);
	}

	while (*s)
	{
		if (*s >= 65 && *s <= 90)
		{
			int i = *s - 64;
			while (i--)
			{
				write(1, s, 1);
			}
		}
		else if (*s >= 97 && *s <= 122)
		{
			int i = *s - 96;
			while (i--)
			{
				write(1, s, 1);
			}
		}
		write(1, s, 1);
		s++;
	}
	return (0);
}