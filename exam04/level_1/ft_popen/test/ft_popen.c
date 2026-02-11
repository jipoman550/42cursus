#include <stdlib.h>
#include <unistd.h>

int	ft_popen(const char *file, char *const argv[], char type)
{
	int	fds[2];

	if (type != 'r' && type != 'w')
		return (-1);
	if (pipe(fds) < 0)
		return (-1);

	int pid = fork();
	if (pid < 0)
	{
		close(fds[0]);
		close(fds[1]);
		return (-1);
	}

	if (pid == 0)
	{
		if (type == 'r')
			dup2(fds[1], STDOUT_FILENO);
		else
			dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
		close(fds[1]);
		execvp(file, argv);
		exit(EXIT_FAILURE);
	}
	else
	{
		if (type == 'r')
		{
			close(fds[1]);
			return (fds[0]);
		}
		else
		{
			close(fds[0]);
			return (fds[1]);
		}
	}
}
