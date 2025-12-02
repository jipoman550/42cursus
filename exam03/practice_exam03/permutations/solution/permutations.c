#include "permutations.h"

int ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

char *ft_strdup(char *src)
{
	if (!src)
		return (NULL);
	int len = ft_strlen(src);
	char *dst = (char *)malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	int i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

void swap(char *a, char *b)
{
	char tmp = *a;
	*a = *b;
	*b = tmp;
}

void sort_str(char *str, int len)
{
	for (int i = 0; i < len - 1; ++i)
	{
		for (int j = 0; j < len - 1 - i; ++j)
		{
			if (str[j] > str[j + 1])
				swap(&str[j], &str[j + 1]);
		}
	}
}

void print_str(char *str)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
}

void reverse(char *str, int start, int end)
{
	while (start < end)
	{
		swap(&str[start], &str[end]);
		start++;
		end--;
	}
}

int next_permutation(char *str, int len)
{
	int i = len - 2;
	while (i >= 0 && str[i] >= str[i + 1])
		i--;

	if (i < 0)
		return (0);

	int j = len - 1;
	while (str[j] <= str[i])
		j--;

	swap(&str[i], &str[j]);

	reverse(str, i + 1, len - 1);

	return (1);
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return (0);

	char *str = ft_strdup(argv[1]);
	if (!str)
		return (1);

	int len = ft_strlen(argv[1]);
	if (len == 0)
	{
		write(1, "\n", 1);
		free(str);
		return (0);
	}

	sort_str(str, len);

	print_str(str);

	while (next_permutation(str, len))
		print_str(str);

	free(str);
	return (0);
}