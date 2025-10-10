// comprehensive_test.c
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include "gnl.h"

void test_case(const char *filename, int expected_lines)
{
    int fd;
    char *line;
    int count = 0;

    printf("\n=== Testing: %s ===\n", filename);

    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        printf("Error: Cannot open %s\n", filename);
        return;
    }

    while ((line = gnl(fd)) != NULL)
    {
        count++;
        printf("Line %d: [", count);
        for (int i = 0; line[i]; i++)
        {
            if (line[i] == '\n')
                printf("\\n");
            else
                printf("%c", line[i]);
        }
        printf("]\n");
        free(line);
    }

    close(fd);

    printf("Result: %d lines (Expected: %d) ", count, expected_lines);
    if (count == expected_lines)
        printf("✓ PASS\n");
    else
        printf("✗ FAIL\n");
}

int main(void)
{
    printf("===================================\n");
    printf("   GNL Comprehensive Test Suite   \n");
    printf("===================================\n");
    printf("BUFFER_SIZE: %d\n", BUFFER_SIZE);

    // 테스트 1: 기본 파일
    test_case("test1.txt", 2);

    // 테스트 2: 빈 줄 포함
    test_case("test2.txt", 4);

    // 테스트 3: 개행 없는 마지막 줄
    test_case("test3.txt", 2);

    // 테스트 4: 빈 파일
    test_case("test4.txt", 0);

    // 테스트 5: 긴 줄
    test_case("test5.txt", 1);

    printf("\n=== All Tests Complete ===\n");
    return 0;
}