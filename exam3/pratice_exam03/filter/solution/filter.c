#define _GNU_SOURCE
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

int perror_and_free(stash, stars)
{
    perror("Error");
    free(stash);
    free(stars);
    return 1;
}

int main(int argc, char* argv[])
{
    // 1. 인자 검사
    if (argc != 2 || argv[1][0] == '\0')
        return 1;

    char buf[BUFFER_SIZE];
    char *stash = NULL;
    size_t stash_len = 0;
    ssize_t r;
    char *pattern = argv[1];
    size_t pat_len = strlen(pattern);

    // 2. 패턴길이 안전성 (이미 인자검사에서 빈 패턴은 막음). 별문자 (stars)를 한 번 만들고 재사용.
    char *stars = malloc(pat_len);
    if (!stars)
    {
        perror("Error: ");
        return 1;
    }
    for (size_t i = 0; i < pat_len; i++)
        stars[i] = '*';

    // 3. read 루프. 데이터 읽고 stash에 붙이기.
    while ((r = read(STDIN_FILENO, buf, BUFFER_SIZE)) > 0)
    {
        char *tmp = realloc(stash, stash_len + r);
        if (!tmp)
            perror_and_free(stash, stars);
        stash = tmp;
        memmove(stash + stash_len, buf, r);
        stash_len += r;

        size_t offset = 0;
        char *pos;

        while ((pos = memmem(stash + offset, stash_len - offset, pattern, pat_len)))
        {

        }


    }

    // 4. stash에서 memmem으로 패턴 찾기. 치환하며 출력.
    // 5. 잔여 데이터 관리  (pat_len - 1 만큼 보관)
    // 6. EOF 시 남은 출력과 정리.

}

