#include <stdio.h>
#include <stdarg.h>

int sum(int count, ...) {
	va_list ap;
	int i;
	int total = 0;

	va_start(ap, count);

	for (i = 0; i < count; i++) {
		total += va_arg(ap, int);
	}

	va_end(ap);

	return total;
}

int main() {
	int result1 = sum(3, 10, 20, 30);
	printf("Sum of 3 numbers: %d\n", result1);

	int result2 = sum(5, 1, 2, 3, 4, 5);
	printf("Sum of 5 numbers: %d\n", result2);

	return 0;
}