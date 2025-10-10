// gnl.c
#include "gnl.h"

static size_t  ft_strlen(const char *s)
{
    size_t i = 0;
    if (!s) return 0;
    while (s[i])
        i++;
    return i;
}

static char    *ft_strchr(const char *s, int c)
{
    if (!s) return NULL;
    while (*s)
    {
        if (*s == (char)c)
            return ((char *)s);
        s++;
    }
    if (*s == (char)c)
        return ((char *)s);
    return NULL;
}

static void    *ft_memcpy(void *dest, const void *src, size_t n)
{
    size_t i = 0;
    if (!dest && !src) return NULL;
    while (i < n)
    {
        ((char *)dest)[i] = ((char *)src)[i];
        i++;
    }
    return dest;
}

// 인덱스를 활용해서 코드를 다시 작성하면 좋을 것 같음. ft_strlen이나 ft_strchr이나 ft_memcpy에는 인덱스를 활용했는데, 활용안하니까 통일성이 떨어지는 느낌.
static void    *ft_memmove(void *dest, const void *src, size_t len)
{
    char *d = (char *)dest;
    const char *s = (const char *)src;
    size_t i;

    if (d == s)
        return (dest);
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
    return (dest);
}

static int str_join_and_free(char **s1, const char *s2, size_t size2)
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

char    *gnl(int fd)
{
    static char b[BUFFER_SIZE + 1] = "";
    char    *ret = NULL;
    char    *tmp;
    ssize_t readbyte;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);

    // 1. Start with the remainder from the last call
	// 이 부분에 대해 자세한 설명이 필요한듯. 예제가 있으면 좋을 듯. 지금 내 생각으로는 BUFFER_SIZE가 전에 gnl로 읽는 과정에서 \n 이 나오기 전에 끝나서 다음 gnl를 불러야할 때를 대비해서 이런건가?
    if (str_join_and_free(&ret, b, ft_strlen(b))) return NULL;

    while (!(tmp = ft_strchr(ret, '\n')))
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
            return ret;
        }
        b[readbyte] = '\0';
        if (str_join_and_free(&ret, b, readbyte)) return NULL;
    }

	// 여기부터 아랫부분은 어떤 기능을 하지는 잘 모르겠음. 자세한설명필요

    // 2. Newline found. Split the string.
    size_t line_len = (tmp - ret) + 1;
    size_t remainder_len = ft_strlen(tmp + 1);

    // Save remainder to static buffer 'b'
    ft_memmove(b, tmp + 1, remainder_len + 1);

    // Create the final line to return
    char *final_line = malloc(line_len + 1);
    if (!final_line)
    {
        free(ret);
        return NULL;
    }
    ft_memcpy(final_line, ret, line_len);
    final_line[line_len] = '\0';

    free(ret);
    return final_line;
}
