#include <unistd.h>

// no use function
int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		write(1, "0\n", 2);
		return 0;
	}

	char *s = argv[1];
	int num = 0;
	int i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
		{
			write(1, "0\n", 2);
			return 0;
		}
		num = num * 10 + (s[i] - '0');
		i++;
	}

	if (num <= 0)
	{
		write(1, "0\n", 2);
		return 0;
	}

	int sum = 0;
	int n = 2;
	while (n <= num)
	{
		int is_prime_flag = 0;
		if (n < 2)
			is_prime_flag = 1;
		i = 2;
		while (i * i <= n)
		{
			if (n % i == 0)
			{
				i++;
				is_prime_flag = 1;
				break;
			}
			i++;
		}
		if (!is_prime_flag)
			sum += n;
		n++;
	}

	if (sum == 0)
	{
		write(1, "0\n", 2);
		return 0;
	}

	int sum_tmp = sum;
	int digit = 0;
	while (sum_tmp > 0)
	{
		digit++;
		sum_tmp = sum_tmp / 10;
	}
	char ret[digit + 1];
	ret[digit] = '\0';

	sum_tmp = sum;
	i = digit - 1;
	while (i >= 0)
	{
		ret[i] = (sum_tmp % 10) + '0';
		sum_tmp /= 10;
		i--;
	}
	write(1, ret, digit);
	write(1, "\n", 1);
	return 0;
}