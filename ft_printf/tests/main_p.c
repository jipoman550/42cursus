#include <stdio.h>
#include "ft_printf.h"

int main()
{
	int* a = NULL;
	char b = 's';
	char *c = "abcd";
	int ret1, ret11, ret2, ret22, ret3, ret33;

	ret1 = printf("%p", a);
	printf("\n");
	ret11 = ft_printf("%p", a);
	printf("\n===============\n");

	ret2 = printf("%p", &b);
	printf("\n");
	ret22 = ft_printf("%p", &b);
	printf("\n===============\n");

	ret3 = printf("%p", &c);
	printf("\n");
	ret33 = ft_printf("%p", &c);
	printf("\n===============\n");

	printf("printf(\"%%p\\n\", a)의 반환 값: %d\n", ret1);
	//ft_printf("ft_printf(\"%%p\\n\", a)의 반환 값: %d\n", ret11); %%와 %d를 구현하고 test해보기
    printf("printf(\"%%p\\n\", &b)의 반환 값: %d\n", ret2);
    //ft_printf("ft_printf(\"%%p\\n\", &b)의 반환 값: %d\n", ret22); %%와 %d를 구현하고 test해보기
    printf("printf(\"%%p\\n\", &c)의 반환 값: %d\n", ret3);
    //ft_printf("ft_printf(\"%%p\\n\", &c)의 반환 값: %d\n", ret33); %%와 %d를 구현하고 test해보기

	return 0;
}