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
	while (s[i] == ' ' || s[i] == '\t')
		i++;

	if (s[i] == '\0')
	{
		write(1, "\n", 1);
		return 0;
	}

	int three_space_needed = 0;
	while (s[i] != '\0')
	{
		if (three_space_needed == 0 && (s[i] != ' ' && s[i] != '\t'))
		{
			write(1, &s[i], 1);
		}
		else if (three_space_needed == 1 && (s[i] != ' ' && s[i] != '\t'))
		{
			three_space_needed = 0;
			write(1, "   ", 3);
			write(1, &s[i], 1);
		}
		else
		{
			three_space_needed = 1;
		}
		i++;
	}
	write(1, "\n", 1);
	return 0;
}