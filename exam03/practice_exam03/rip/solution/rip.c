#include "rip.h"

void get_min_removals(char *s, int *l_rem, int *r_rem)
{
	int bal = 0;
	*l_rem = 0;
	*r_rem = 0;

	for (int i = 0; s[i]; i++)
	{
		if (s[i] == '(')
			bal++;
		else if (s[i] == ')')
		{
			if (bal > 0)
				bal--;
			else
				(*r_rem)++;
		}
	}
	*l_rem = bal;
}

int rip_is_valid(char *pset)
{
	int bal = 0;

	for (int i = 0; pset[i]; i++)
	{
		if (pset[i] == '(')
			bal++;
		else if (pset[i] == ')')
			bal--;

		if (bal < 0)
			return (0);
	}
	return (bal == 0);
}

void rip_recursive(char *pset, int start_idx, int l_rem, int r_rem)
{
	if (l_rem == 0 && r_rem == 0)
	{
		if (rip_is_valid(pset))
			puts(pset);
		return ;
	}

	for (int i = start_idx; pset[i]; i++)
	{
		if (pset[i] != '(' && pset[i] != ')')
			continue ;

		if (pset[i] == '(' && l_rem > 0)
		{
			pset[i] = ' ';
			rip_recursive(pset, i + 1, l_rem - 1, r_rem);
			pset[i] = '(';
		}

		if (pset[i] == ')' && r_rem > 0)
		{
			pset[i] = ' ';
			rip_recursive(pset, i + 1, l_rem, r_rem - 1);
			pset[i] = ')';
		}
	}
}

int main(int ac, char **av)
{
	if (ac != 2 || !av[1])
		return (0);

	int l_rem = 0;
	int r_rem = 0;

	get_min_removals(av[1], &l_rem, &r_rem);

	rip_recursive(av[1], 0, l_rem, r_rem);

	return (0);
}