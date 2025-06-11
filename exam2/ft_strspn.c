#include <stdio.h>
#include <string.h>

size_t ft_strspn(const char *s, const char *accept)
{
	int i, j, check;

	i = 0;
	while (s[i])
	{
		j = 0;
		check = 0;
		while (accept[j])
		{
			if (s[i] == accept[j])
			{
				check = 1;
			}
			j++;
		}
		if (check == 0)
		{
			return (i);
		}
		i++;
	}
	return (i);
}

int main()
{
	char *s = "hello";
	const char *accept = "123h4e5l6l7890";
	printf("%zu\n", ft_strspn(s, accept));
	printf("%ld\n", strspn(s, accept));
}

// s : scan 할 문자열
// accept :