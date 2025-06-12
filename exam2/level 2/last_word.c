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