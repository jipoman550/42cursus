#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int picoshell(char **cmds[])
{
	int i = 0;
	int pipe_fds[2];
	int prev_read_end = -1; // 이전 파이프의 읽기 끝 저장

	while (cmds[i])
	{
		// 마지막 명령어가 아니라면 파이프 생성
		if (cmds[i + 1])
		{
			if (pipe(pipe_fds) == -1)
				return 1;
		}

		pid_t pid = fork();
		if (pid == -1)
			return 1;

		if (pid == 0)
		{ // 자식 프로세스
			// 1. 이전 파이프에서 입력 받기
			if (prev_read_end != -1)
			{
				dup2(prev_read_end, STDIN_FILENO);
				close(prev_read_end);
			}
			// 2. 현재 파이프로 출력 보내기
			if (cmds[i + 1])
			{
				close(pipe_fds[0]); // 읽기 끝은 닫음
				dup2(pipe_fds[1], STDOUT_FILENO);
				close(pipe_fds[1]);
			}
			// 명령어 실행
			execvp(cmds[i][0], cmds[i]);
			exit(1); // execvp 실패 시
		}
		else
		{ // 부모 프로세스
			if (prev_read_end != -1)
				close(prev_read_end);
			if (cmds[i + 1])
			{
				close(pipe_fds[1]); // 쓰기 끝은 닫음
				prev_read_end = pipe_fds[0]; // 다음 명령어를 위해 읽기 끝 저장
			}
		}
		i++;
	}

	// 모든 자식 프로세스 대기
	while (wait(NULL) > 0);
	return 0;
}