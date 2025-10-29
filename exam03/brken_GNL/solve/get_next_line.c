#include "get_next_line.h"

size_t ft_strlen(const char *s)
{
	int i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char *ft_strchr(char *s, int c)
{
	while (s && *s)
	{
		if (*s == (char)c)
			return s + 1;
		s++;
	}
	return NULL;
}
void *ft_memcpy(char *dest, char *src, size_t size)
{
	int i = -1;
	while (++i < (int)size)
		dest[i] = src[i];
	return dest;
}

void *ft_memmove(char *dest, char *src, size_t size)
{
	if (dest < src)
		return ft_memcpy(dest, src, size);
	if (dest == src)
		return dest;
	size_t n = size;
	dest[n] = 0;
	while (n > 0)
	{
		dest[n - 1] = src[n - 1];
		n--;
	}
	return dest;
}

int str_add_mem(char **s2, char *s1, size_t size1)
{
	size_t size2 = ft_strlen(*s2);
	char *tmp = malloc(size2 + size1 + 1);
	if (!tmp)
		return 1;
	ft_memmove(tmp, *s2, size2);
	ft_memmove(tmp + size2, s1, size1);
	tmp[size2 + size1] = 0;
	ft_memmove(s1, s1 + size1, ft_strlen(s1 + size1) + 1);
	free(*s2);
	*s2 = tmp;
	return 0;
}


int str_add_str(char **s2, char *s1, size_t size)
{
	char *tmp = ft_strchr(s1, '\n');
	if (tmp)
		return 2;
	int i = str_add_mem(s2, s1, size);
	return i;
}

char *get_next_line(int fd)
{
	static char b[BUFFER_SIZE + 1] = "";
	int readbyte;
	char *ret = NULL;
	char *tmp;
	if (BUFFER_SIZE <= 0)
		return NULL;
	while (!(tmp = ft_strchr(b, '\n')))
	{
		int sig = str_add_str(&ret, b, ft_strlen(b));
		if (sig == 1)
			return NULL;
		else if (sig == 2)
			break ;
		readbyte = read(fd, b, BUFFER_SIZE);
		if (readbyte == -1)
		{
			if (ret)
				free(ret);
			return NULL;
		}
		if (readbyte == 0)
		{
			if (ret && *ret)
				return ret;
			free(ret);
			return NULL;
		}
		b[readbyte] = 0;
	}
	if (str_add_mem(&ret, b, tmp - b))
		return NULL;
	return ret;
}


























