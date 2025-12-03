//get_next_line.c

#include "gnl.h"

char *ft_strchr(char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t i = 0;
	if (!dest || !src)
		return (NULL);
	while (i < n)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return dest;
}

size_t ft_strlen(char *s)
{
	size_t res = 0;
	if (!s)
		return (0);
	while (*s)
	{
		s++;
		res++;
	}
	return res;
}

int str_join_and_free(char **s1, char *s2, size_t size2)
{
	size_t size1 = ft_strlen(*s1);
	char *tmp = malloc(size1 + size2 + 1);
	if (!tmp)
	{
		free(*s1);
		*s1 = NULL;
		return (1);
	}
	if (*s1)
		ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
	tmp[size1 + size2] = '\0';
	free(*s1);
	*s1 = tmp;
	return (0);
}
//int str_append_mem(char **s1, char *s2, size_t size2)
//{
//	size_t size1 = ft_strlen(*s1);
//	char *tmp = malloc(size2 + size1 + 1);
//	if (!tmp)
//		return 0;
//	ft_memcpy(tmp, *s1, size1);
//	ft_memcpy(tmp + size1, s2, size2);
//	tmp[size1 + size2] = '\0';
//	free(*s1);
//	*s1 = tmp;
//	return 1;
//}

//int str_append_str(char **s1, char *s2)
//{
//	return str_append_mem(s1, s2, ft_strlen(s2));
//}

void *ft_memmove(void *dest, const void *src, size_t n)
{
	char *d = (char *)dest;
	const char *s = (const char *)src;
	size_t i;

	if (d == s)
		return (dest);
	if (d < s)
	{
		i = 0;
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	else
	{
		i = n;
		while (i > 0)
		{
			i--;
			d[i] = s[i];
		}
	}
	return dest;
}

char *get_next_line(int fd)
{
	static char b[BUFFER_SIZE + 1] = "";
	char *ret = NULL;
	char *tmp;
	ssize_t readbyte;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	if (str_join_and_free(&ret, b, ft_strlen(b)))
		return (NULL);

	while(!(tmp = ft_strchr(ret, '\n')))
	{
		readbyte = read(fd, b, BUFFER_SIZE);

		if (readbyte <= 0)
		{
			b[0] = '\0';
			if (readbyte == -1 || !ret || ret[0] == '\0')
			{
				free(ret);
				return (NULL);
			}
			return (ret);
		}
		b[readbyte] = '\0';
		if (str_join_and_free(&ret, b, readbyte))
			return (NULL);
	}

	size_t line_len = (tmp - ret) + 1;
	size_t remainder_len = ft_strlen(tmp + 1);

	ft_memmove(b, tmp + 1, remainder_len + 1);

	char *final_line = malloc(line_len + 1);
	if (!final_line)
	{
		free(ret);
		return (NULL);
	}
	ft_memcpy(final_line, ret, line_len);
	final_line[line_len] = '\0';
	free(ret);
	return final_line;
}