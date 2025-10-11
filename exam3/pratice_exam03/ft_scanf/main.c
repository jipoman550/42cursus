#include <stdio.h>

/* ft_scanf 함수 원형 */
int ft_scanf(const char *format, ...);

int main(void)
{
    int n;
    char c;
    char str[128];

    printf("==== Test 1: %%d ====\n");
    printf("Input an integer: ");
    if (ft_scanf("%d", &n) == 1)
        printf("You entered: %d\n", n);
    else
        printf("Failed to read integer.\n");

    /* 입력 버퍼 비움용: 남은 개행문자 소비 */
    while (getchar() != '\n' && !feof(stdin))
        ;

    printf("\n==== Test 2: %%s ====\n");
    printf("Input a word: ");
    if (ft_scanf("%s", str) == 1)
        printf("You entered: \"%s\"\n", str);
    else
        printf("Failed to read string.\n");

    while (getchar() != '\n' && !feof(stdin))
        ;

    printf("\n==== Test 3: %%c ====\n");
    printf("Input a single character (space also valid): ");
    if (ft_scanf("%c", &c) == 1)
        printf("You entered: '%c' (ascii %d)\n", c, (int)c);
    else
        printf("Failed to read char.\n");

    while (getchar() != '\n' && !feof(stdin))
        ;

    printf("\n==== Test 4: %%d %%s %%c mixed ====\n");
    printf("Input format: <int> <word> <char>\n");
    printf("Example input: 42 hello x\n");
    if (ft_scanf("%d %s %c", &n, str, &c) == 3)
        printf("Parsed: %d, \"%s\", '%c'\n", n, str, c);
    else
        printf("Failed to match all.\n");

    return 0;
}
