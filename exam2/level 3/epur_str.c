/*
1. 파라미터 2개가 아니면 개행 처리
2. s[i]를 통해 문자 끝이 아니고 공백이면 인덱스 패싱
3. 문자끝이면 (파라미터 공백  " ") 개행처리
4. space_needed 플래그를 통해 공백을 만나면 1로 처리하고 인덱스 증가
5. space_needed 플래그가 1이고 공백이 아니면 공백 하나 찍어주고 문자출력
*/

#include <unistd.h>

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		write(1, "\n", 1);
		return 0;
	}

	char *s = argv[1];

	int i = 0;
	while (s[i] != '\0' && (s[i] == ' ' || s[i] == '\t'))
	{
		i++;
	}

	if (s[i] == '\0')
	{
		write(1, "\n", 1);
		return 0;
	}

	int space_needed = 0;
	while (s[i] != '\0')
	{
		if (s[i] == ' ' || s[i] == '\t')
		{
			space_needed = 1;
		}
		else
		{
			if (space_needed == 1)
			{
				write(1, " ", 1);
				space_needed = 0;
			}
			write(1, &s[i], 1);
		}
		i++;
	}
	write(1, "\n", 1);

	return 0;
}