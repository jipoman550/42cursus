#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid < 0 )
		return (-1);

	if (pid == 0)
	{
		alarm(timeout);
		f();
		exit(0);
	}

	if (waitpid(pid, &status, 0) == -1)
		return (-1);

	if (WIFEXITED(status))
	{
		int exit_code = WEXITSTATUS(status);
		if (exit_code == 0)
		{
			if (verbose)
				printf("Nice function!\n");
			return (1);
		}
		else
		{
			if (verbose)
				printf("Bad function: exited with code %d\n", exit_code);
			return (0);
		}
	}
	else if (WIFSIGNALED(status))
	{
		int sig = WTERMSIG(status);
		if (sig == SIGALRM)
		{
			if (verbose)
				printf("Bad function: timed out after %u seconds\n", timeout);
		}
		else
		{
			if (verbose)
				printf("Bad function: %s\n", strsignal(sig));
		}
		return (0);
	}

	return (0);
}