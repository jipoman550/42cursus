#include <stdio.h>

char *ft_strpbrk(const char *s1, const char *s2)
{
	int i, j;

	i = 0;
	while (s1[i])
	{
		j = 0;
		while(s2[j])
		{
			if (s2[j] == s1[i])
				return ((char *)&s1[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}