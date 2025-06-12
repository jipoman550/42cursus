#include <unistd.h>

int main(int argc, char *argv[])
{
	if (argc == 3)
	{
		char *s1 = argv[1];
		char *s2 = argv[2];
		int lookup[256] = {};
		int i = 0;
		while(s1[i])
			lookup[(int)s1[i++]] = 1;
		i = 0;

		while (s2[i])
			lookup[(int)s2[i++]] = 1;
		i = 0;

		while (s1[i])
		{
			if (lookup[(int)s1[i]])
			{
				write(1, &s1[i], 1);
				lookup[(int)s1[i]] = 0;
			}
			i++;
		}
		i = 0;
		while (s2[i])
		{
			if (lookup[(int)s2[i]])
			{
				write(1, &s2[i], 1);
				lookup[(int)s2[i]] = 0;
			}
			i++;
		}
	}
	write(1, "\n", 1);
	return 0;
}