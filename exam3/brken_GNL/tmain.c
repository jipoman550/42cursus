#include "get_next_line.h"
#include <fcntl.h>

int main(void)
{
	char *tcase[6] = {"/home/jaeholee/SUBJECT/git_forder/exam3/brken_GNL/case1.txt", \
				"/home/jaeholee/SUBJECT/git_forder/exam3/brken_GNL/case2.txt", \
				"/home/jaeholee/SUBJECT/git_forder/exam3/brken_GNL/case3.txt", \
				"/home/jaeholee/SUBJECT/git_forder/exam3/brken_GNL/case4.txt", \
				"/home/jaeholee/SUBJECT/git_forder/exam3/brken_GNL/case5.txt", \
				"/home/jaeholee/SUBJECT/git_forder/exam3/brken_GNL/case6.txt" \
				};
	
	int i = 0;
	char *readstr;
	while (i < 6)
	{
		if (i == 2){
			i++;
			continue ;
		}
		int fd = open(tcase[i], O_RDONLY);
		if (fd == -1){
			i++;
			continue ;
		}
		printf("======test_case %d %dstart=======\n", i + 1, fd);
		while (1)
		{
			readstr = get_next_line(fd);
			if (!readstr)
			{
				printf("NULLLLLL\n");
				break ;
			}
			if (!*readstr)
			{
				printf("NULLLLLL2222222222\n");
				break ;
			}
			printf("gnl read: =%s=-=-=-=-=-=-=-=-=-\n", readstr);
			free(readstr);
		}
		printf("======test_case %d end =======\n", i + 1);
		free(readstr);
		close(fd);
		i++;
	}
	return (0);
}

