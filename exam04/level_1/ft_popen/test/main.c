#include <unistd.h>
#include <stdio.h>

int ft_popen(const char *command, char *const argv[], char type);

int main()
{
	char *args_ls[] = {"ls", "-l", NULL};
	int fd_r = ft_popen("ls", args_ls, 'r');
	if (fd_r == -1)
	{
		perror("ft_popen for 'ls' failed");
		return (1);
	}

	char buf[1024];
	int n;
	while ((n = read(fd_r, buf, sizeof(buf) - 1)) > 0)
	{
		buf[n] = '\0';
		printf("My program read: %s", buf);
	}
	close(fd_r);

	char *arg_grep[] = {"grep", "hello", NULL};
	int fd_w = ft_popen("grep", arg_grep, 'w');
	if (fd_w == -1)
	{
		perror("ft_open for 'grep failed");
		return (1);
	}

	write(fd_w, "hello world! I'm sisung\n", 24);
	write(fd_w, "this is test\n", 13);
	close(fd_w);

	return (0);
}