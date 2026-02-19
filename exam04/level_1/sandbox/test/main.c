#include <stdbool.h>
#include <stdlib.h>

int sandbox(void (*f)(void), unsigned int timeout, bool verbose);

void good_func() {};
void segfault_func() { int *p = NULL; *p = 42; };
void timeout_func() { while (1); };
void bad_exit_func() { exit(42); };

int main()
{
	sandbox(good_func, 1, true);
	sandbox(segfault_func, 1, true);
	sandbox(timeout_func, 1, true);
	sandbox(bad_exit_func, 1, true);

	return (0);
}