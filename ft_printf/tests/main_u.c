#include <stdio.h>
#include "ft_printf.h"

int main() {
	int ret1, ret11;

    printf("%u", 123);
	printf("\n");
	ft_printf("%u", 123);
	printf("\n");

	ret1 = printf("%u", -123); // 4294967173가 나왔는데 이게 뭐냐.
	printf("\n");
	ret11 = ft_printf("%u", -123);
	printf("\n");

	printf("%u", 0);
	printf("\n");
	ft_printf("%u", 0);
	printf("\n");

    // printf("%u", 123.123); double 이기 때문에 UB.

	//printf("%u", NULL); UB 이기 때문에 구현하지 않아도 됨.
	//printf("\n");
	//ft_printf("%u", NULL);
	//printf("\n");

	printf("printf return result :%d", ret1);
	printf("\n");
	printf("printf return result :%d", ret11);
	printf("\n");

    return 0;
}