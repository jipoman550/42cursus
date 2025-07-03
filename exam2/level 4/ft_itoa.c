#include <stdlib.h>

char	*ft_itoa(int nbr)
{
	int digit = 0;
	long long int num = nbr;
	if (nbr <= 0)
		digit++;
	while (num != 0)
	{
		num /= 10;
		digit++;
	}

	char * ret;
	ret = (char *)malloc(sizeof(char) * (digit + 1));
	if (!ret)
		return (NULL);

	ret[digit] = '\0';
	int i = digit - 1;
	num = nbr;
	if (nbr < 0)
	{
		ret[0] = '-';
		num = -num;
	}
	while (num > 9)
	{
		ret[i] = num % 10 + '0';
		num = num / 10;
		i--;
	}
	ret[i] = num + '0';
	return (ret);
}
#include <stdio.h>

int main()
{
	int n = 123;
	char *s = ft_itoa(-2147483648);
	printf("%s", s);
	free(s);

	return 0;
}