#include <stdio.h>

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}
int main(void)
{
	char *s = ft_strchr("aaabbbccc\nddd", '\n');
	printf("%s\n", s);
	return (0);
}