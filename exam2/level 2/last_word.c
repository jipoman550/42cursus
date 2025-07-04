/*
1. 인덱스를 맨 뒤로 보냄
2. 뒤에서부터 인덱스가 0보다 크거나 같고 space bar || \t이면 인덱스를 감소시킴
3. 인덱스가 0보다 작아지면 \n 출력
4. 마지막 단어의 마지막 인덱스를 저장해
5. 인덱스가 0보다 크고, 공백(spacebar, /t)이면 인덱스 감소시켜서 마지막 단어의 시작인덱스 바로 전 공백의 인덱스를 찾아냄.
6. 공백인덱스++ 부터 아까 저장한 마지막 단어의 마지막 인덱스까지 배열을 읽으면서 출력
7. 마지막에 \n 출력 잊지말고.
*/

#include <unistd.h>

int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		char *s = argv[1];
		int i = 0;
		while (s[i] != '\0')
		{
			i++;
		}
		i--;
		while (i >= 0 && (s[i] == ' ' || s[i] == '\t'))
		{
			i--;
		}
		if (i < 0)
		{
			write(1, "\n", 1);
			return 0;
		}
		int end_of_word_index = i;
		while (i >= 0 && s[i] != ' ' && s[i] != '\t')
		{
			i--;
		}
		int start_of_word_index = i + 1;
		while (start_of_word_index <= end_of_word_index)
		{
			write(1, &s[start_of_word_index], 1);
			start_of_word_index++;
		}
		write(1, "\n", 1);
		return (0);
	}
	else
	{
		write(1, "\n", 1);
	}
	return 0;
}