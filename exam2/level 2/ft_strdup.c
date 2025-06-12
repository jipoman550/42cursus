#include <stdlib.h>

char *ft_strdup(char *src)
{
	int len = 0;
	while (src[len])
	{
		len++;
	}
	char *ret = (char *)malloc(sizeof(char) * len + 1);
	if (!ret)
		return (NULL);
	int i = 0;
	while (i < len)
	{
		ret[i] = src[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

#include <stdio.h>

int main()
{
	char *s = "hehe ojum balSSA";
	printf("%s \n", ft_strdup(s));

	return 0;
}