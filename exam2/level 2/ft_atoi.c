
int ft_isdigit(char c)
{
	return (c >= 48 && c <= 57 ? 1 : 0);
}

int ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32 ? 1  : 0);
}

int ft_atoi(const char *str)
{
	int ret = 0;
	int i = 0;
	int s = 1;

	while (ft_isspace(str[i]))
	{
		i++;
	}

	if (str[i] == '-')
	{
		s = -1;
		i++;
	}

	while (ft_isdigit(str[i]))
	{
		ret *= 10;
		ret += str[i] - 48;
		i++;
	}

	return (ret *= s);
}
#include <stdio.h>

int main()
{
	char *s1 = "1234";
	char *s2 = "-1234";

	printf("%s\n", s1);
	printf("%s\n", s2);

	return 0;
}