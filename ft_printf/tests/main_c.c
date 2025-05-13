#include "ft_printf.h"
#include <stdio.h>

int main()
{
	int a;
	a = ft_printf(NULL);
	ft_printf("%d\n", a);

	/*printf("%c", NULL);
	ft_printf("%c", NULL);

	ft_printf("What's up bro,\n");
	ft_printf("My name is %c!\n", 'S');

	printf("What's up bro,\n");
	printf("My name is %c!\n", 'S');
	printf("================\n");

	// c가 NULL일 때
	// ft_printf는 컴파일이 되고, 실행파일을 실행하면 %c가 없던 것으로 출력됨.
	// printf는 컴파일부터 안됨.
	ft_printf("What's up bro,\n");
	ft_printf("My name is %c!\n", NULL);

	printf("What's up bro,\n");
	printf("My name is %c!\n", NULL);*/
	return 0;
}