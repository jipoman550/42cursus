#include <fcntl.h> // open()
#include "get_next_line.h"

int main(void)
{
	int fd = 0;
	char *result = NULL;

	fd = open("example.txt", O_RDONLY);
	while ((result = get_next_line(fd)) != NULL)
	{
		printf("%s", result);
		free(result);
	}
	close(fd);
	return 0;
}