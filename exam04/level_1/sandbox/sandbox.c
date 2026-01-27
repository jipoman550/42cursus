#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>

int sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid < 0)
		return -1;

	if (pid == 0)
	{
		// 자식 프로세스: 타이머 설정 후 함수 실행
		alarm(timeout);
		f();
		// 함수가 성공적으로 종료되면 exit(0)
		_exit(0);
	}

	// 부모 프로세스: 자식이 종료될 때까지 대기 (좀비 방지)
	if (waitpid(pid, &status, 0) == -1)
		return -1;

	// 1. 정상적으로 종료된 경우 (exit 호출)
	if (WIFEXITED(status))
	{
		int exit_code = WEXITSTATUS(status);
		if (exit_code == 0)
		{
			if (verbose)
				printf("Nice function!\n");
			return 1;
		}
		else
		{
			if (verbose)
				printf("Bad function: exited with code %d\n", exit_code);
			return 0;
		}
	}
	// 2. 시그널에 의해 종료된 경우 (세그폴트, 타임아웃 등)
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
		return 0;
	}

	return 0;
}