#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

int sandbox(void (*f)(void), unsigned int timeout, bool verbose);

void good_func() { /* 아무것도 안 함 */ }
void segfault_func() { int *p = NULL; *p = 42; }
void infinite_func() { while(1); }
void exit_bad_func() { exit(42); } // 0이 아닌 에러 코드로 종료

int main() {
	printf("--- Test 1: Good ---\n");
	sandbox(good_func, 2, true);

	printf("\n--- Test 2: Segfault ---\n");
	sandbox(segfault_func, 2, true);

	printf("\n--- Test 3: Timeout ---\n");
	sandbox(infinite_func, 2, true);

	printf("\n--- Test 4: Exit with Code 42 ---\n");
	sandbox(exit_bad_func, 2, true);

	return 0;
}