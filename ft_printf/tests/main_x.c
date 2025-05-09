#include <stdio.h>
#include "ft_printf.h"

int main() {
	int ret1, ret11, ret2, ret22;

    ret1 = printf("printf :%x", 0xAB123);
	printf("\n");
	ret11 = ft_printf("ft_printf :%x", 0xAB123);
	printf("\n");
    ret2 = printf("printf :%X", 0xab123);
	printf("\n");
	ret22 = ft_printf("ft_printf :%X", 0xAB123);
	printf("\n");
	printf("printf :%d", ret1);
	printf("\n");
	ft_printf("ft_printf :%d", ret11);
	printf("\n");
    printf("printf :%d", ret2);
	printf("\n");
	ft_printf("ft_printf :%d", ret22);
	printf("\n");
	printf("\n");

	ret1 = printf("printf :%x", 123);
	printf("\n");
	ret11 = printf("ft_printf :%x", 123);
	printf("\n");
    ret2 = printf("printf :%X", 123);
	printf("\n");
	ret22 = printf("ft_printf :%X", 123);
	printf("\n");
	printf("printf :%d", ret1);
	printf("\n");
	ft_printf("ft_printf :%d", ret11);
	printf("\n");
    printf("printf :%d", ret2);
	printf("\n");
	ft_printf("ft_printf :%d", ret22);
	printf("\n");

	/*// unsigned int 만 한다. 그러므로 음수는 제외인듯?
	// but! 어차피 unsigned int로 타입 캐스팅을 하기 때문에 자동적으로 될 듯함.
	printf("printf :%x", -123);
	printf("\n");
	printf("ft_printf :%x", -123);
	printf("\n");
    printf("printf :%X", -123);
	printf("\n");
	printf("ft_printf :%X", -123);
	printf("\n");

	printf("printf :%x", 0);
	printf("\n");
	printf("ft_printf :%x", 0);
	printf("\n");
    printf("printf :%X", 0);
	printf("\n");
	printf("ft_printf :%X", 0);
	printf("\n");*/

	// NULL은 UB 인듯.
	//printf("%x", NULL);
	//printf("\n");
    //printf("%X", NULL);
	//printf("\n");

    return 0;
}