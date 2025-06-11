#include <unistd.h>

int main(int argc, char* argv[])
{
	if (argc == 2)
	{
		char *s = argv[1];
		int i = 0;
		while (s[i] != '\0')
		{
			if (s[i] >= 65 && s[i] <= 90)
			{
				write(1, "_", 1);
				char c = s[i] + 32;
				write(1, &c, 1);
			}
			else
			{
				write(1, &s[i], 1);
			}
			i++;
		}
		return 0;
	}
	write(1, "\n", 1);
	return 0;
}