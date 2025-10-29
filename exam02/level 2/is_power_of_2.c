int is_power_of_2(unsigned int n)
{
	if (n == 0)
		return 0;

	while (n % 2 == 0)
	{
		n /= 2;
	}

	return (n == 1);
}

/*int	    is_power_of_2(unsigned int n)
{
	int test = 1;

	while (test <= n)
	{
		if (test == n)
			return  (1); // test is a power of 2
		test = test * 2;
	}
	return (0);
}*/


#include <stdio.h>

int main()
{
	printf("%d\n", is_power_of_2(15));

	return 0;
}