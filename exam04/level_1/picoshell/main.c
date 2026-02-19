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

/*
// txt 파일에 있는 예시 버전 test
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int picoshell(char **cmds[]);

int main(int argc, char **argv)
{
	if (argc < 2) return 0;

	// 대략적인 명령어 배열 생성 (최대 100개 가정)
	char ***cmds = calloc(argc, sizeof(char **));
	int cmd_idx = 0;
	int arg_start = 1;

	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "|") == 0)
		{
			argv[i] = NULL; // 파이프를 NULL로 바꿔서 execvp 종료 표시
			cmds[cmd_idx++] = &argv[arg_start];
			arg_start = i + 1;
		}
	}
	cmds[cmd_idx++] = &argv[arg_start];
	cmds[cmd_idx] = NULL;

	return picoshell(cmds);
}
*/
