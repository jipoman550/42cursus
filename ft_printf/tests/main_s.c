#include "ft_printf.h"
#include <stdio.h>

int main()
{
	printf("hi my name is %s!\n", "");
	ft_printf("hi my name is %s!", "");

	// s가 NULL일 때 printf는 컴파일과정에서 오류가 남.
	// ft_printf는 컴파일은 완료되고 실행파일을 실행하면 segmemtation fault (core dumped) 가 난다.
	printf("hi my name is %s!\n", NULL);
	ft_printf("hi my name is %s!", NULL);

	return 0;
}