#include <stdio.h>
#include <stdarg.h>

void va_fct(int a, ...);

int main(void)
{
	va_fct(1, 1);
	va_fct(2, 1, 2);
	va_fct(3, 1, 2, 3);

    return 0;
}

void va_fct(int a, ...)
{
	va_list list;

	va_start(list, a);

	for (int i = 0; i < a; i++) {
		printf("%d ", va_arg(list, int));
	}
	printf("\n");

	va_end(list);
}