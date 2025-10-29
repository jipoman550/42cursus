#include <unistd.h>

int ft_atoi(char *s)
{
	int len = 0;
	while (s[len])
		len++;
	int ret = 0;
	int i = 0;
	while (i < len)
	{
		int a = s[i] - '0';
		ret = ret * 10 + a;
		i++;
	}
	return ret;
}

void ft_putnbr(int num)
{
	if (num >= 10)
	{
		ft_putnbr(num / 10);
		ft_putnbr(num % 10);
	}
	else
	{
		char c = num + '0';
		write(1, &c, 1);
	}
}

int main(int argc, char *argv[])
{
	if (argc <= 1)
	{
		write(1, "\n", 1);
		return 0;
	}

	char *n = argv[1];
	int num = ft_atoi(n);
	int i = 1;
	while (i <= 9)
	{
		char c1 = i + '0';
		write(1, &c1, 1);
		write(1, " x ", 3);
		ft_putnbr(num);
		write(1, " = ", 3);
		ft_putnbr(i * num);
		write(1, "\n", 1);
		i++;
	}

	return 0;
}