int max(int* tab, unsigned int len)
{
	int cnt = 0;
	int ret = 0;
	int i = 0;
	if (len > 0)
	{
		while (cnt < len)
		{
			if (tab[i] > ret)
				ret = tab[i];
			i++;
			cnt++;
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