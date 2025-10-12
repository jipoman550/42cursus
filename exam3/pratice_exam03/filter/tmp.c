// 실험 2: realloc(stash, stash_len + r) vs malloc(stash_len + r)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char *stash_realloc = NULL;
    char *stash_malloc = NULL;
    size_t stash_len = 0;

    // 첫 번째 데이터: "ab"
    char buf[] = "ab";
    size_t r = strlen(buf);

    // realloc으로 데이터 추가
    char *tmp_realloc = realloc(stash_realloc, stash_len + r);
    if (!tmp_realloc)
    {
        perror("Error");
        free(stash_realloc);
        return 1;
    }
    stash_realloc = tmp_realloc;
    memcpy(stash_realloc + stash_len, buf, r);
    stash_len += r;
    printf("After realloc (ab): %.*s\n", (int)stash_len, stash_realloc);

    // malloc 으로 데이터 추가 (잘못된 사용)
    char *tmp_malloc = malloc(stash_len + r);
    if (!tmp_malloc)
    {
        perror("Error");
        free(stash_realloc);
        return 1;
    }
    memcpy(tmp_malloc, buf, r); // 기존 데이터 복사 안함
    stash_malloc = tmp_malloc;
    printf("After malloc (ab): %.*s\n", (int)r, stash_malloc);

    // 두 번쨰 데이터: "cd"
    strcpy(buf, "cd");
    r = strlen(buf);

    //realloc 으로 데이터 추가
    tmp_realloc = realloc(stash_realloc, stash_len + r);
    if (!tmp_realloc)
    {
        perror("Error");
        free(stash_realloc);
        free(stash_malloc);
        return 1;
    }
    stash_realloc = tmp_realloc;
    memcpy(stash_realloc + stash_len, buf, r);
    stash_len += r;
    printf("After realloc (ab + cd): %.*s\n", (int)stash_len, stash_realloc);

    // malloc 으로 데이터 추가 (잘못된 사용)
    tmp_malloc = malloc(stash_len + r);
    if (!tmp_malloc)
    {
        perror("Error");
        free(stash_realloc);
        free(stash_malloc);
        return 1;
    }
    memcpy(tmp_malloc, buf, r); // 기존 데이터 복사 안함
    free(stash_malloc); // 이전 메모리 해제
    stash_malloc = tmp_malloc;
    printf("After malloc (cd): %.*s\n", (int)r, stash_malloc);

    // 메모리 해제
    free(stash_realloc);
    free(stash_malloc);

    return 0;
}