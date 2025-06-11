#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(int argc, char **argv)
{
	int fd;
	char *result = NULL;
	int i = 1;
	const char *filename;

	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s <file>\n", argv[0]);
		return 1;
	}
	filename = argv[1];

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return 1;
	}

	while ((result = get_next_line(fd)) != NULL)
	{
		printf("line[%d]: %s", i, result);
		free(result);
		i++;
	}

	if (close(fd) < 0)
	{
		perror("close");
		return 1;
	}

	return 0;
}