#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#define BUFFER_SIZE 4096

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
    // 3. read 루프. 데이터 읽고 stash에 붙이기.
    // 4. stash에서 memmem으로 패턴 찾기. 치환하며 출력.
    // 5. 잔여 데이터 관리  (pat_len - 1 만큼 보관)
    // 6. EOF 시 남은 출력과 정리.

}

