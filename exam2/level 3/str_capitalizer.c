#include <unistd.h>

int is_space(char c)
{
	if (c >= 8 && c <= 13 || c == 32)
		return 1;
	return 0;
}

int main(int argc, char *argv[])
{
	if (argc <= 1)
	{
		write(1, "\n", 1);
		return 0;
	}

	int i = 1;
	while(i < argc)
	{
		int j = 0;
		while (argv[i][j] != '\0')
		{
			if (argv[i][0] >= 'a' && argv[i][0] <= 'z')
			{
				argv[i][j] -= 32;
			}
			else if ((argv[i][j] >= 'a' && argv[i][j] <= 'z') && (is_space(argv[i][j - 1])))
			{
				argv[i][j] -= 32;
			}
			else if ((argv[i][j] >= 'A' && argv[i][j] <= 'Z') && !is_space(argv[i][j - 1]))
			{
				argv[i][j] += 32;
			}
			write(1, &argv[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}

	return 0;
}

/*#include <unistd.h>

int ft_isspace(char c)
{
    if (c <= 32)
        return (1);
    return (0);
}

void ft_putchar(char c)
{
    write(1, &c, 1);
}

void capitalizer(char *s)
{
    int i = 0;
    while (s[i])
    {
         if (s[i] >= 'A' && s[i] <= 'Z')
             s[i] += 32;
         if ((s[i] >= 'a' && s[i] <= 'z') && ft_isspace(s[i - 1]))
             s[i] -= 32;
         ft_putchar(s[i++]);
    }
}

int main(int ac, char **av)
{
    int i = 1;
    if (ac == 1)
        ft_putchar('\n');
    else
    {
        while (i < ac)
        {
            capitalizer(av[i]);
            ft_putchar('\n');
            i++;
        }
    }
}*/
