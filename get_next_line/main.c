#include <fcntl.h> // open()
#include "get_next_line.h"

int main(void)
{
	int fd = 0;
	char *result = NULL;

	fd = open("example.txt", O_RDONLY);
	int i = 1;
	while ((result = get_next_line(fd)) != NULL)
	{
		printf("line[%d]: %s", i, result);
		free(result);
		i++;
	}
	close(fd);
	return 0;
}