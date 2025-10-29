int max(int* tab, unsigned int len)
{
	int ret;
	unsigned int i = 0;
	if (len > 0)
	{
		ret = tab[0];
		while (i < len)
		{
			if (tab[i] > ret)
				ret = tab[i];
			i++;
		}
		return (ret);
	}
	return (0);
}

#include <stdio.h>

int main()
{
	int int_tab[] = {1, 3, 2, 100, 9};
	printf("%d\n", max(int_tab, 5));
}