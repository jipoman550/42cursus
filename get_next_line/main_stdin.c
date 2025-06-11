#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
	char *line;
	int i = 1;

	printf("Type something (Ctrl-D to exit):\n");

	while ((line = get_next_line(0)) != NULL) // fd = 0 is stdin
	{
		printf("line[%d]: %s", i++, line);
		free(line);
	}
	printf("\n[EOF detected, exiting]\n");
	return 0;
}
