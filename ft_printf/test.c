#include <stdio.h>

int main()
{
	int* a = NULL;
	char b = 's';
	char *c = "abcd";
	int ret1, ret2, ret3;

	ret1 = printf("%p", a);
	printf("\n");
	ret2 = printf("%p", &b);
	printf("\n");
	ret3 = printf("%p", &c);
	printf("\n");

	printf("printf(\"%%p\\n\", a)의 반환 값: %d\n", ret1);
    printf("printf(\"%%p\\n\", &b)의 반환 값: %d\n", ret2);
    printf("printf(\"%%p\\n\", &c)의 반환 값: %d\n", ret3);

	return 0;
}