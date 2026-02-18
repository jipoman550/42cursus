#include <sys/wait.h>
#include <unistd.h>

int ft_popen(const char *file, char *const argv[], char type)
{
	int fds[2];
	pid_t pid;

	if (pipe(fds) == -1)
		return (-1);

	pid = fork();
	if (pid == -1)
	{
		close(fds[0]);
		close(fds[1]);
		return (-1);
	}

	while (argv[i])
	{
		if (pid == 0)
		{
			if (type == 'r')
			{
				dup2(fds[1], STDOUT_FILENO);
				close(fds[1]);
			}
			else
			{
				dup2(fds[0], STDIN_FILENO);
				close(fds[0]);
			}
			execvp(file, argv[i]);
			exit(1);
		}
		else
		{
			if (type == 'r')
				close(fds[0]);
			else
				close(fds[1]);
		}
		i++;
	}

}