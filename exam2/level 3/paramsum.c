#include <unistd.h>

void ft_putnbr(int num)
{
	if (num >= 10)
	{
		ft_putnbr(num / 10);
		ft_putnbr(num % 10);
	}
	else
	{
		char c = num % 10 + '0';
		write(1, &c, 1);
	}
}

int main(int argc, char *argv[])
{
	if (argc <= 1)
	{
		write(1, &"0", 1);
	}
	else
	{
		ft_putnbr(argc - 1);
	}
	write(1, "\n", 1);

	return 0;
}