#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int    picoshell(char **cmds[])
{
	int fds[2];
	int i = 0;
	int prev_read_end = -1;

	while (cmds[i])
	{
		if (cmds[i + 1])
		{
			if (pipe(fds) == -1)
				return (1);
		}

		int pid = fork();
		if (pid == -1)
		{
			if (prev_read_end != -1)
				close(prev_read_end);
			if (cmds[i + 1])
			{
				close(fds[0]);
				close(fds[1]);
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
				close(fds[0]);
				dup2(fds[1], STDOUT_FILENO);
				close(fds[1]);
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
				close(fds[1]);
				prev_read_end = fds[0];
			}
		}
		i++;
	}

	while (wait(NULL) > 0);
	return (0);
}

#include <stdio.h>

int main()
{
	char *cmd1[] = {"ls", "-la", NULL};
	char *cmd2[] = {"grep", "picoshell", NULL};
	char *cmd3[] = {"wc", "-l", NULL};

	char **pipeline[] = {cmd1, cmd2, cmd3, NULL};

	if (picoshell(pipeline) != 1)
		printf("success!\n");
	else
		printf("fail!\n");
	return (0);
}