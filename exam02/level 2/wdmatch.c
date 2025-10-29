/*
1. s1[i]와 s2[j]가 same이면 i++해줌.j는 계속 ++ 해줌.
2. s1[i] == '\0' 을 만나면 조건에 만족한다는 것이니까 s1을 len길이 만큼 출력.
*/

#include <unistd.h>

int main(int argc, char *argv[])
{
	if (argc == 3)
	{
		char * s1 = argv[1];
		char * s2 = argv[2];
		int len = 0, i = 0, j = 0;

		while (s1[len])
			len++;

		while (s1[i] != '\0' && s2[j] != '\0')
		{
			if (s1[i] == s2[j])
				i++;
			j++;
		}
		if (s1[i] == '\0')
		{
			write(1, s1, len);
			write(1, "\n", 1);
		}
		else
		{
			write(1, "\n", 1);
		}
	}
	else
	{
		write(1, "\n", 1);
	}
	return 0;
}