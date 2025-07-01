#include <unistd.h>

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		write(1, "\n", 1);
		return 0;
	}

	char *s = argv[1];

	int i = 0;
	while (s[i] != '\0' && (s[i] == ' ' || s[i] == '\t'))
	{
		i++;
	}

	if (s[i] == '\0')
	{
		write(1, "\n", 1);
		return 0;
	}

	int space_needed = 0;
	while (s[i] != '\0')
	{
		if (s[i] == ' ' || s[i] == '\t')
		{
			space_needed = 1;
		}
		else
		{
			if (space_needed == 1)
			{
				write(1, " ", 1);
				space_needed = 0;
			}
			write(1, &s[i], 1);
		}
		i++;
	}
	write(1, "\n", 1);

	return 0;
}