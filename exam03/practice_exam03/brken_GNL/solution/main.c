// 파일 1개만 test
#include "gnl.h" // get_next_line 함수 선언이 포함된 헤더 파일
#include <stdio.h>  // printf, perror 사용
#include <fcntl.h>  // open 함수 사용
#include <unistd.h> // close 함수 사용
#include <stdlib.h> // free 함수 사용 (get_next_line의 반환값을 해제해야 함)

#ifndef FILE_NAME
# define FILE_NAME "file.txt"
#endif

int main(void)
{
    char    *line;
    int     line_count = 0;

    // 1. 테스트할 파일 열기
    // O_RDONLY: 읽기 전용으로 파일 열기
    int fd = open(FILE_NAME, O_RDONLY);

    if (fd < 0)
    {
        perror("Error opening file");
        return (1); // 파일 열기 실패 시 종료
    }

    printf("--- Start reading file: %s ---\n", FILE_NAME);

    // 2. get_next_line을 반복 호출하여 한 줄씩 읽기
    while ((line = get_next_line(fd)) != NULL)
    {
        line_count++;
        // 읽은 줄을 콘솔에 출력 (줄바꿈 문자가 이미 포함되어 있다면 printf("%s", ...)만 사용)
        // gnl 구현 상 줄바꿈 문자가 포함되어 반환되므로, %s만 사용합니다.
        printf("[Line %d]: %s", line_count, line);

        // get_next_line이 malloc으로 할당한 메모리 해제
        free(line);
    }

    // 마지막으로 읽기가 끝나거나 오류가 발생했을 때 (line == NULL)
    if (line_count > 0)
        printf("--- End of file. Total lines read: %d ---\n", line_count);
    else if (line_count == 0)
        printf("--- File is empty or read error occurred. ---\n");

    // 3. 파일 디스크립터 닫기
    close(fd);

    return (0);
}

/* main.c
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
    while ((line = get_next_line(fd)) != NULL)
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
        "test3.txt", // x 개많음
        "test1.txt", // aaaaa
        "test2.txt", // bbbbb
        "test4.txt", // 빈 파일
        "test5.txt", // \n
        "test6.txt", // foo\n\nbar\n
        "test7.txt", // \n\n\n\n\n
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
    char *line = get_next_line(-1);
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
}*/
