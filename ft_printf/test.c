#include <stdio.h>

int main() {
    int a = -123;
	unsigned int b = a;

	printf("%u", b); // 4294967173가 나왔는데 이게 뭐냐
	printf("\n");

    return 0;
}