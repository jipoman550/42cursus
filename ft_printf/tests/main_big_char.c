#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "ft_printf.h"

int main(void)
{
	// 파이프 생성
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    // 쓰기용 파이프의 출력 방향을 stdout으로 바꿈
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[1]);  // write만 남기고, 원래 fd 닫음

    // 읽기용 파이프는 닫아서 SIGPIPE 유도
    close(pipefd[0]);

    // 많은 출력 (출력 도중 SIGPIPE 발생 유도)
    int ret = ft_printf("%01000000a\n");  // 매우 긴 출력 (a를 백만 개 이상 찍기)
    printf("ft_printf returned: %d\n", ret);
    perror("errno");

	/*const char *msg = "Hello42Gyeongsan!";
    int ret1, ret2;
    size_t i;

    // Print many times to potentially trigger write error
    for (i = 0; i < 10000000000; i++)
    {
        // Use libc printf
        ret1 = printf("%s\n", msg);
        if (ret1 < 0)
        {
            fprintf(stderr, "[libc printf] write error occurred at i=%zu\n", i);
            break;
        }

        // Use your own ft_printf
        ret2 = ft_printf("%s\n", msg);
        if (ret2 < 0)
        {
            write(2, "[ft_printf] write error occurred\n", 33);
            break;
        }
    }*/

    return 0;
}
