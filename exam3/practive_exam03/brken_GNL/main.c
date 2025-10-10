// main.c
#include "gnl.h"
#include <fcntl.h>
#include <stdio.h>

void run_test(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        printf("!!! Error opening file: %s !!!\n\n", filename);
        return;
    }

    printf("---[ Output for %s ]---\n", filename);
    char *line;
    int line_num = 1;
    while ((line = gnl(fd)) != NULL)
    {
        printf("[%d]: %s", line_num++, line);
        free(line);
    }
    printf("---[ End of %s ]---\n", filename);
    close(fd);
}

int main(void)
{
    const char *files[] = {
        "case1.txt", // aaaaa
        "case2.txt", // bbbbb
        "case3.txt", // x 개많음
        "case4.txt", // 빈 파일
        "case5.txt", // \n
        "case6.txt", // foo\n\nbar\n
        "case7.txt", // \n\n\n\n\n
        "test_with_nl.txt", // hello\n
        "test_without_nl.txt", // hello
        NULL
    };

    for (int i = 0; files[i] != NULL; i++)
    {
        run_test(files[i]);
    }

    // Test with invalid fd
    printf("---[ Testing invalid fd (-1) ]---\n");
    char *line = gnl(-1);
    if (line == NULL)
    {
        printf("Result: gnl correctly returned NULL.\n");
    }
    else
    {
        printf("Result: gnl did NOT correctly handle invalid fd.\n");
        free(line);
    }
    printf("---[ End of invalid fd test ]---\n");

    return 0;
}