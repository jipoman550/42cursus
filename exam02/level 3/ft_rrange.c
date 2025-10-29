#include <stdlib.h>

int     *ft_rrange(int start, int end)
{
	int len;
	int pyosik;
	if (start < end)
	{
		len = end - start + 1;
		pyosik = 1;
	}
	else if (start > end)
	{
		len = start - end + 1;
		pyosik = 2;
	}
	else
	{
		len = 1;
		pyosik = 3;
	}

	int *ret = (int *)malloc(sizeof(int) * len);
	if (!ret)
		return 0;

	int i = 0;
	while (i < len)
	{
		if (pyosik == 1)
		{
			ret[i] = end;
			i++;
			end--;
		}
		else if (pyosik == 2)
		{
			ret[i] = end;
			i++;
			end++;
		}
		else
		{
			ret[i] = end;
			i++;
		}
	}
	return (ret);
}

/*#include <stdio.h>

int main()
{
	int *ret1 = ft_rrange(1, 3);
	int *ret2 = ft_rrange(-1, 2);
	int *ret3 = ft_rrange(0, 0);
	int *ret4 = ft_rrange(0, -3);

	printf("ret1: ");
	if (ret1)
	{
		for (int i = 0; i < (3 - 1 + 1); i++)
		{
			printf("%d ", ret1[i]);
		}
		free(ret1);
	}
	else
	{
		printf("메모리 할당 실패");
	}
	printf("\n");

	printf("ret2: ");
	if (ret2)
	{
		for (int i = 0; i < (2 - (-1) + 1); i++)
		{
			printf("%d ", ret2[i]);
		}
		free(ret2);
	}
	else
	{
		printf("메모리 할당 실패");
	}
	printf("\n");

	printf("ret3: ");
	if (ret3)
	{
		for (int i = 0; i < (0 - 0 + 1); i++)
		{
			printf("%d ", ret3[i]);
		}
		free(ret3);
	}
	else
	{
		printf("메모리 할당 실패");
	}
	printf("\n");

	printf("ret4: ");
	if (ret1)
	{
		for (int i = 0; i < (0 - (-3) + 1); i++)
		{
			printf("%d ", ret4[i]);
		}
		free(ret4);
	}
	else
	{
		printf("메모리 할당 실패");
	}
	printf("\n");
	return 0;
}*/