#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	size_t	cnt;

	cnt = 0;
	while (*s)
	{
		cnt++;
		s++;
	}
	return (cnt);
}

int main(void)
{
	ft_strlen(NULL);

	return (0);
}