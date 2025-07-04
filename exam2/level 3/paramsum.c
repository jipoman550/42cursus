/*
int argc에서 argc는 정수이기 때문에, 이걸 char 형으로 바꾸어 write로 찍는게 중요함. 10이상일 때 해주어야
*/

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