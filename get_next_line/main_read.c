#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
	int fd = open("example.txt", O_RDONLY);
	char *line;
	int i = 1;

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("line[%d]: %s", i++, line);
		free(line);
	}
	close(fd);
	return 0;
}