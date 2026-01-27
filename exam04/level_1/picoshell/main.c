#include <stdio.h>

// picoshell 프로토타입
int picoshell(char **cmds[]);

int main(void)
{
	// 1. "ls -l" 명령어 준비
	char *cmd1[] = {"ls", "-l", NULL};
	// 2. "grep picoshell" 명령어 준비
	char *cmd2[] = {"grep", "picoshell", NULL};
	// 3. "wc -l" 명령어 준비
	char *cmd3[] = {"wc", "-l", NULL};

	// 명령어들을 하나로 묶음 (NULL로 끝남을 표시)
	char **pipeline[] = {cmd1, cmd2, cmd3, NULL};

	printf("--- 파이프라인 실행 시작 ---\n");

	// ls -l | grep picoshell | wc -l 실행
	if (picoshell(pipeline) == 0)
	{
		printf("--- 실행 성공 ---\n");
	}
	else
	{
		printf("--- 실행 중 오류 발생 ---\n");
	}

	return 0;
}