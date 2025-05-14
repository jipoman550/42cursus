#include <stdio.h>
#include "ft_printf.h"

int main(void)
{
	int ret1, ret2;
	void *ptr = (void *)0x1234abcd;
	char *null_str = NULL;

	// %c
	printf("========== %%c ==========\n");
	ret1 = printf("printf: [%c]\n", 'A');
	ret2 = ft_printf("ft_printf: [%c]\n", 'A');
	printf("ret printf: %d, ft_printf: %d\n\n", ret1, ret2);

	// %s
	printf("========== %%s ==========\n");
	ret1 = printf("printf: [%s]\n", "Hello");
	ret2 = ft_printf("ft_printf: [%s]\n", "Hello");
	printf("ret printf: %d, ft_printf: %d\n", ret1, ret2);

	ret1 = printf("printf NULL: [%s]\n", null_str);
	ret2 = ft_printf("ft_printf NULL: [%s]\n", null_str);
	printf("ret printf: %d, ft_printf: %d\n\n", ret1, ret2);

	// %p
	printf("========== %%p ==========\n");
	ret1 = printf("printf: [%p]\n", ptr);
	ret2 = ft_printf("ft_printf: [%p]\n", ptr);
	printf("ret printf: %d, ft_printf: %d\n", ret1, ret2);

	ret1 = printf("printf NULL ptr: [%p]\n", NULL);
	ret2 = ft_printf("ft_printf NULL ptr: [%p]\n", NULL);
	printf("ret printf: %d, ft_printf: %d\n\n", ret1, ret2);

	// %d, %i
	printf("========== %%d / %%i ==========\n");
	ret1 = printf("printf: [%d]\n", 1234);
	ret2 = ft_printf("ft_printf: [%d]\n", 1234);
	printf("ret printf: %d, ft_printf: %d\n", ret1, ret2);

	ret1 = printf("printf: [%i]\n", -5678);
	ret2 = ft_printf("ft_printf: [%i]\n", -5678);
	printf("ret printf: %d, ft_printf: %d\n\n", ret1, ret2);

	// %u
	printf("========== %%u ==========\n");
	ret1 = printf("printf: [%u]\n", 4294967295u);
	ret2 = ft_printf("ft_printf: [%u]\n", 4294967295u);
	printf("ret printf: %d, ft_printf: %d\n\n", ret1, ret2);

	// %x, %X
	printf("========== %%x / %%X ==========\n");
	ret1 = printf("printf: [%x]\n", 305441741);
	ret2 = ft_printf("ft_printf: [%x]\n", 305441741);
	printf("ret printf: %d, ft_printf: %d\n", ret1, ret2);

	ret1 = printf("printf: [%X]\n", 305441741);
	ret2 = ft_printf("ft_printf: [%X]\n", 305441741);
	printf("ret printf: %d, ft_printf: %d\n\n", ret1, ret2);

	// %%
	printf("========== %%%% ==========\n");
	ret1 = printf("printf: [%%]\n");
	ret2 = ft_printf("ft_printf: [%%]\n");
	printf("ret printf: %d, ft_printf: %d\n\n", ret1, ret2);

	// Mixed Format
	printf("========== Mixed Format ==========\n");
	ret1 = printf("printf: [%c][%s][%p][%d][%u][%x][%X][%%]\n", 'Z', "42Gyeongsan", ptr, -42, 42, 255, 255);
	ret2 = ft_printf("ft_printf: [%c][%s][%p][%d][%u][%x][%X][%%]\n", 'Z', "42Gyeongsan", ptr, -42, 42, 255, 255);
	printf("ret printf: %d, ft_printf: %d\n\n", ret1, ret2);

	// Edge Cases
	printf("========== Edge Cases ==========\n");
	ret1 = printf("printf empty str: [%s]\n", "");
	ret2 = ft_printf("ft_printf empty str: [%s]\n", "");
	printf("ret printf: %d, ft_printf: %d\n", ret1, ret2);

	ret1 = printf("printf max int: [%d]\n", 2147483647);
	ret2 = ft_printf("ft_printf max int: [%d]\n", 2147483647);
	printf("ret printf: %d, ft_printf: %d\n", ret1, ret2);

	ret1 = printf("printf min int: [%d]\n", (int)-2147483648);
	ret2 = ft_printf("ft_printf min int: [%d]\n", -2147483648);
	printf("ret printf: %d, ft_printf: %d\n\n", ret1, ret2);

	int ret42 = ft_printf("ft_printf max int: [%f]\n\n", 2147483647);
	ft_printf("\n%d", ret42);
	printf("\n%d", ret42);
	printf("\n\n");

	// 에러 유도 테스트 (write 실패 시 -1 확인)
	// 1. stdout을 잘못된 fd로 임시 교체
    int len;
    int fd;

	fd = dup(1);           // stdout 백업
	close(1);              // stdout 닫음 -> write 실패 유도
	len = ft_printf("this should fail\n");
	if (len == -1)
		write(fd, "ft_printf correctly returned -1 on write failure\n", 49);
	else
		write(fd, "ft_printf did NOT return -1 (BUG)\n", 33);
	dup2(fd, 1);           // stdout 복구
	close(fd);
	return (0);
}
