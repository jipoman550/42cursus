#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int    picoshell(char **cmds[])
{
	int i = 0;
	int pipe_fds[2];
	int prev_read_end = -1;

	while (cmds[i])
	{
		if (cmds[i + 1])
		{
			if (pipe(pipe_fds) < 0)
				return (1);
		}

		pid_t pid = fork();
		if (pid < 0)
		{
			if (prev_read_end != -1)
				close(prev_read_end);
			if (cmds[i + 1])
			{
				close(pipe_fds[0]);
				close(pipe_fds[1]);
			}
			return (1);
		}

		if (pid == 0)
		{
			if (prev_read_end != -1)
			{
				dup2(prev_read_end, STDIN_FILENO);
				close(prev_read_end);
			}
			if (cmds[i + 1])
			{
				close(pipe_fds[0]);
				dup2(pipe_fds[1], STDOUT_FILENO);
				close(pipe_fds[1]);
			}
			execvp(cmds[i][0], cmds[i]);
			exit(1);
		}
		else
		{
			if (prev_read_end != -1)
				close(prev_read_end);
			if (cmds[i + 1])
			{
				close(pipe_fds[1]);
				prev_read_end = pipe_fds[0];
			}
		}
		i++;
	}

	while (wait(NULL) > 0);
	return (0);
}