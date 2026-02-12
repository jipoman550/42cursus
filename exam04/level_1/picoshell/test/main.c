#include <stdio.h>

int    picoshell(char **cmds[]);

int main()
{
	char *cmd1[] = {"ls", "-l", NULL};
	char *cmd2[] = {"grep", "picoshell", NULL};
	char *cmd3[] = {"wc", "-l", NULL};

	char **pipeline[] = {cmd1, cmd2, cmd3, NULL};

	printf("------ 파이프라인 실행 시작 ------- \n");

	if (picoshell(pipeline) == 0)
	{
		printf("--- 실행 성공 ---\n");
	}
	else
	{
		printf("--- 실행 중 오류 발생 ---\n");
	}

	return (0);
}