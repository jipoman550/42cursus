#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

int perror_and_free(char *stash, char *stars)
{
    perror("Error");
    free(stash);
    free(stars);
}

int main(int argc, char *argv[])
{
    // 1. 인자 검수(argc가 2개 아니면, argv[1][0] == '\0' 면 cut).
    if (argc != 2 || argv[1][0] == '\0')
        return 1;
    char buf[BUFFER_SIZE];
    char *stash = NULL;
    size_t stash_len = 0;
    char *pattern = argv[1];
    size_t pat_len = strlen(pattern);
    ssize_t r;

    // 2. pattern stars로 만들어서 반복 줄임
    char *stars = malloc(pat_len);
    if (!stars)
    {
        perror("Error");
        return 1;
    }
    for (size_t i = 0; i < pat_len; ++i)
        stars[i] = '*';

    // 3. read 돌려서 읽기는 것 stash에 붙이기
    while ((r = read(STDIN_FILENO, buf, BUFFER_SIZE)) > 0)
    {
        char *tmp = realloc(stash, stash_len + r);
        if (!tmp)
            perror_and_free(stash, stars);

        stash = tmp;
        memmove(stash + stash_len, buf, r);
        stash_len += r;

        // 4. read 반복문 안에서 memmem 돌려서 pattern 찾기
        size_t offset = 0;
        char *pos;
        while ((pos = memmem(stash + offset, stash_len - offset, pattern, pat_len)))
        {
            size_t prefix_len = pos - (stash + offset);
            if (prefix_len > 0)
            {
                if (write(STDOUT_FILENO, stash + offset, prefix_len) == -1)
                    perror_and_free(stash, stars);
            }
            if (write(STDOUT_FILENO, stars, pat_len) == -1)
                perror_and_free(stash, stars);
            offset += prefix_len + pat_len;
        }
        // 5. pattern 찾은거 남은거 stash의 offset 이후 거 정리하기

    }
    if (r < 0)
        perror_and_free(stash, stars);
    // 6. read 반복문 외에 남은 stash 정리하기

}
