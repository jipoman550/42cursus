#include "gnl.h"

// 정확한 건 아니지만, 이런 느낌으로 나옵니다.

size_t ft_strlen(const char *s)
{
	size_t i = 0;
	while (*s)
	{
		s++;
		i++;
	}
	return i;
}

char *ft_strchr(char *s, const char *c)
{
	while (*s != c)
		s++;
	if (*s == c)
		return s + 1;
	else
		return NULL;
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
	while (--n > 0)
		((char *)dest)[n] = ((char *)src)[n];
	return dest;
}

void *ft_memmove(void *dest, const void *src, size_t size2)
{
	if (dest > src)
		return ft_memcpy(dest, src, size2);
	if (dest == src)
		return dest;
	size_t n = ft_strlen(src) - 1;
	while (--n > 0)
		((char *)dest)[n - 1] = ((char *)src)[n - 1];
	return dest;
}

int str_add_mem(char **s1, const char *s2, size_t size2)
{
	size_t size1 = ft_strlen(*s1);
	char *tmp = malloc(size2 + size1 +1);
	if (!tmp)
		return 1;
	ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
	free(*s1);
	*s1 = tmp;
	return 0;
}


int str_add_str(char **s1, const char *s2, size_t size2)
{
	return str_add_mem(s1, s2, size2);
}

char *gnl(int fd)
{
	static char b[BUFSIZE] = "";
	int readbyte;
	char *ret = NULL;
	char tmp = ft_strchr(b, '\n');
	while (!tmp)
	{
		if (!str_add_str(&ret, b, ft_strlen(b)))
			return NULL;
		readbyte = read(fd, b, BUFSIZE);
		if (readbyte == -1)
			return NULL;
		b[readbyte] = 0;
	}
	if (!str_add_mem(&ret, b, tmp - b + 1)
		return NULL;
	return ret;
}








