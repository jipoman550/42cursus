#include <unistd.h>
/*#include <stdlib.h>

int ft_strlen(char *s)
{
	int len = 0;
	while (s[len] != '\0')
	{
		len++;
	}
	return (len);
}


int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		write(1, "\n", 1);
		return 0;
	}

	char *str = argv[1];
	int len = ft_strlen(str);
	int i = 0;
	int word_cnt = 0;
	char **words;

	if (len > 0)
	{
		word_cnt = 1;
		i = 0;
		while (i < len)
		{
			if (str[i] == ' ')
				word_cnt++;
			i++;
		}
	}

	if (word_cnt == 0)
	{
		write(1, "\n", 1);
		return 0;
	}

	words = (char **)malloc(sizeof(char *) * word_cnt);
	if (!words)
		return 1;

	i = 0;
	int current_word_index = 0;
	if (len > 0)
	{
		words[current_word_index++] = &str[0];
		while (i < len)
		{
			if (str[i] == ' ')
				words[current_word_index++] = &str[i + 1];
			i++;
		}
	}

	i = word_cnt - 1;
	while (i >= 0)
	{
		char *word_start = words[i];
		int word_len = 0;

		while (word_start[word_len] && word_start[word_len] != ' ')
			word_len++;

		write(1, word_start, word_len);

		if (i > 0)
			write(1, " ", 1);

		i--;
	}

	write(1, "\n", 1);

	free(words);

	return 0;
}*/

int	main(int ac, char **av)
{
	int i;
	int j;
	int first_word;

	i = 0;
	first_word = 0;
	if (ac == 2)
	{
		while (av[1][i] != '\0')
			i++;
		i--;
		while (i >= 0)
		{
			while (i >= 0 && (av[1][i] == ' ' || av[1][i] == '\t'))
				i--;
			j = i;
			while (j >= 0 && av[1][j] != ' ' && av[1][j] != '\t')
				j--;
			if (first_word)
				write(1, " ", 1);
			write(1, &av[1][j + 1], i - j);
			first_word = 1;
			i = j;
		}
	}
	write(1, "\n", 1);
	return (0);
}

/*
1. 인덱스를 맨뒤로 보내
2. 인덱스--. 인덱스 >= 0 이고 공백이 있으면 패싱.
3. 단어 만나면 거기가 단어끝 인덱스
4. j를 이용해서 단어처음 인덱스를 찾아
5. i와 j의 차이를 이용해서 단어길이 찾아서 write 찍기
6. 첫단어는 공백없게하고 뒤에서 부터는 공백있게 하면 됨. first_word가 플래그역할.
*/