#include <unistd.h>

int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		char *s = argv[1];
		int i = 0;
		if (s[i] == ' ')
		{
			write(1, "\n", 1);
			return 0;
		}
		while (s[i] != '\0')
		{
			i++;
		}
		i--;
		while (s[i] == 32 || s[i] == '\t')
		{
			i--;
		}
		while (s[i] > 32 && s[i] != '\t')
		{
			i--;
		}
		i++;
		while (s[i])
		{
			write(1, &s[i], 1);
			i++;
		}
		return (0);
	}
	write(1, "\n", 1);
	return 0;
}