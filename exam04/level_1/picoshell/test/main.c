#include <stdio.h>

int    picoshell(char **cmds[]);

int main()
{
	char *cmd1[] = {"ls", "-l", NULL};
	char *cmd2[] = {"grep", "picoshell", NULL};
	char *cmd3[] = {"wc", "-l", NULL};

	char **pipeline[] = {cmd1, cmd2, cmd3, NULL};

	printf("---------------시작----------------\n");

	if (picoshell(pipeline) == 0)
	{
		printf("-------sucess!--------\n");
	}
	else
	{
		printf("-------fail...:(--------\n");
	}

	return (0);
}