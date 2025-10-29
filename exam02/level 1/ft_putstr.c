#include <unistd.h>

void *ft_putstr(char *str)
{
	char *ptr = str;
	while (*ptr)
	{
		write(1, *ptr, 1);
		ptr++;
	}
}