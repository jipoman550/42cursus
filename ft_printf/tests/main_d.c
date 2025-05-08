#include <stdio.h>
#include "ft_printf.h"

int main() {
    printf("printf :%d", 123);
	printf("\n");
    ft_printf("ft_printf :%d", 123);
	printf("\n");

    printf("printf :%d", 2147483647);
	printf("\n");
    ft_printf("ft_printf :%d", 2147483647);
	printf("\n");

    printf("printf :%d", (int)-2147483648);
	printf("\n");
    ft_printf("ft_printf :%d", -2147483648);
	printf("\n");

	/* ?? %d 에 -2147483648를 출력하려고 할 때
	 printf일 때 : 컴파일에서 오류 뜸. a./out파일 실행하면 오버플로우 나타나서 2147483647 출력.
	 그러면 ft_printf일 때도 위랑 같이 해야됨? 아니면 오버플로우 나타나는 것으로 해야됨?
	 -> 답변 : 너가 말한 경우는 UB이기 때문에 무시해야도 됨. (int)-2147483648을 printf에 넣었을 때랑 같은 값을 출력하게 하면 됨.*/
    return 0;
}