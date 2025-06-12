#include <stdlib.h>

int     *ft_range(int start, int end)
{
	int len = 0;
	int len = (end - start) < 0 ? ((end - start) * -1) + 1 : (end - start) + 1;
	int *ret = (int *)malloc(sizeof(int) * len);
	if (!ret)
		return (NULL);

	int i = 0;
	if (start >= end)
	{
		while (i < len)
		{
			ret[i] = start;
			i++;
			start++;
		}
	}
	else if (start < end)
	{
		while (i < len)
		{
			ret[i] = start;
			i++;
			start--;
		}
	}
	return (ret);
}