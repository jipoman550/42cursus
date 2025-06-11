#include <unistd.h>

int main(int argc, char* argv[])
{
	if (argc == 2)
	{
		char *s = argv[1];
		int i = 0;
		if (s[i] == '\0')
		{
			write(1, "\n", 1);
			return 0;
		}
		while (s[i] != '\0')
		{
			if (s[i] >= 65 && s[i] <= 90)
			{
				if (s[i] == 'z')
				{
					s[i] = 'a';
				}
				else
				{
					s[i] = s[i] + 1;
				}
				write(1, &s[i], 1);
			}
			else if (s[i] >= 97 && s[i] <= 122)
			{
				if (s[i] == 'Z')
				{
					s[i] = 'A';
				}
				else
				{
					s[i] = s[i] + 1;
				}
				write(1, &s[i], 1);
			}
			else
			{
				write(1, &s[i], 1);
			}
			i++;
		}
		write(1, "\n", 1);
		return 0;
	}
	write(1, "\n", 1);
	return 0;
}