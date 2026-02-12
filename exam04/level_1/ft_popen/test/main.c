#include <stdio.h>
#include <unistd.h>

int ft_popen(const char *file, char *const argv[], char type);

int main()
{
	char *arg[] = {"ls", "-la", NULL};
	int fd_r = ft_popen("ls", arg, 'r');
	if (fd_r == -1)
	{
		perror("Error가 났다!");
		return (-1);
	}

	int n;
	char buf[1024];
	while ((n = read(fd_r, buf, sizeof(buf) - 1)) > 0)
	{
		buf[n] = '\0';
		printf("%s\n", buf);
	}
	close(fd_r);
	return (0);
}