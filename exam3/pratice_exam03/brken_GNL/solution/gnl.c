#include "gnl.h"

size_t  ft_strlen(const char *s)
{
    size_t i = 0;
    if (!s)
        return 0;
    while (s[i])
        i++;
    return i;
}

char    *ft_strchr(char *s, const char c)
{
    if (!s)
        return NULL;
    while (*s)
    {
        if (*s == (char)c)
            return ((char *)s);
        s++;
    }
    if (*s == (char)c)
        return (char *)s;
    return NULL;
}

void    *ft_memcpy(void *dest, const void *src, size_t n)
{
    size_t i = 0;
    if (!dest && !src)
        return NULL;
    while (i < n) // ⚠️ off-by-one 버그
    {
        ((char *)dest)[i] = ((char *)src)[i];
        i++;
    }
    return dest;
}

void    *ft_memmove(void *dest, const void *src, size_t len)
{
    char *d = (char *)dest;
    const char *s = (const char *)src;
    size_t i;
    if (d == s)
        return dest;
    if (d < s)
    {
        i = 0;
        while (i < len)
        {
            d[i] = s[i];
            i++;
        }
    }
    else
    {
        i = len;
        while (i > 0)
        {
            i--;
            d[i] = s[i];
        }
    }
    return dest;
}
int str_join_and_free(char **s1, const char *s2, size_t size2)
{
    size_t size1 = ft_strlen(*s1);
    char *tmp = malloc(size1 + size2 + 1);
    if (!tmp)
    {
        free(*s1);
        *s1 = NULL;
        return 1;
    }
    if (*s1)
        ft_memcpy(tmp, *s1, size1);
    ft_memcpy(tmp + size1, s2, size2);
    tmp[size1 + size2] = '\0';
    free(*s1);
    *s1 = tmp;
    return 0;    
}

//int str_add_mem(char **s1, const char *s2, size_t size2)
//{
//    size_t size1 = ft_strlen(*s1); // ⚠️ *s1 이 NULL일 때 문제
//    char *tmp = malloc(size1 + size2 + 1);
//    if (!tmp)
//        return 1;
//    ft_memcpy(tmp, *s1, size1);
//    ft_memcpy(tmp + size1, s2, size2);
//    free(*s1);
//    *s1 = tmp;
//    return 0;
//}

//int str_add_str(char **s1, const char *s2, size_t size2)
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