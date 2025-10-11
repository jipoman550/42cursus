#include "gnl.h"

size_t  ft_strlen(const char *s)
{
    size_t i = 0;
    while (*s)
    {
        s++;
        i++;
    }
    return i;
}

char    *ft_strchr(char *s, const char c)
{
    while (*s && *s != c)
        s++;
    if (*s == c)
        return s + 1;
    return NULL;
}

void    *ft_memcpy(void *dest, const void *src, size_t n)
{
    while (--n > 0) // ⚠️ off-by-one 버그
        ((char *)dest)[n] = ((char *)src)[n];
    return dest;
}

void    *ft_memmove(void *dest, const void *src, size_t size2)
{
    if (dest > src)
        return ft_memcpy(dest, src, size2);
    if (dest == src)
        return dest;
    size_t n = ft_strlen(src) - 1; // ⚠️ strlen 사용은 잘못됨
    while (--n > 0)
        ((char *)dest)[n - 1] = ((char *)src)[n - 1];
    return dest;
}

int str_add_mem(char **s1, const char *s2, size_t size2)
{
    size_t size1 = ft_strlen(*s1); // ⚠️ *s1 이 NULL일 때 문제
    char *tmp = malloc(size1 + size2 + 1);
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

char    *gnl(int fd)
{
    static char b[BUFFER_SIZE + 1] = "";
    int     readbyte;
    char    *ret = NULL;
    char    *tmp;

    tmp = ft_strchr(b, '\n');
    while (!tmp)
    {
        if (str_add_str(&ret, b, ft_strlen(b)))
            return NULL;
        readbyte = read(fd, b, BUFFER_SIZE);
        if (readbyte == -1)
            return NULL;
        b[readbyte] = 0;
        tmp = ft_strchr(b, '\n');
    }
    if (str_add_mem(&ret, b, tmp - b + 1)) // ⚠️ 괄호 오류 가능
        return NULL;
    return ret;
}