#include "rip.h"

int	rip_is_valid(char *pset)
{
	int balance = 0;

	for (int i = 0; pset[i]; i++)
	{
		if (pset[i] == '(')
			balance++;
		else if (pset[i] == ')')
			balance--;

		if (balance < 0)
			return 0;
	}
	return (balance == 0);
}

void	get_min_removals(char *s, int *l_rem, int *r_rem)
{
	int balance = 0;
	*l_rem = 0;
	*r_rem = 0;

	for (int i = 0; s[i]; i++)
	{
		if (s[i] == '(')
		{
			balance++;
		}
		else if (s[i] == ')')
		{
			if (balance > 0)
				balance--;
			else
				(*r_rem)++;
		}
	}
	*l_rem = balance;
}

void	rip_recursive(char *pset, int start_index, int l_rem, int r_rem)
{
	// 재귀 종료 조건: 제거해야 할 괄호가 더 이상 없으면
	if (l_rem == 0 && r_rem == 0)
	{
		if (rip_is_valid(pset))
			puts(pset);
		return ;
	}

	// DFS 탐색: start_index 부터 문자열 끝까지 순회하며 제거할 괄호를 찾음.
	for (int i = start_index; pset[i]; i++)
	{
		// 현재 문자가 괄호가 아니면 건너뜀
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

int	main(int ac, char **av)
{
	if (ac != 2 || !av[1])
		return 0;

	int l_rem = 0;
	int r_rem = 0;

	// 제거해야 할 최소 괄호 수 계산
	get_min_removals(av[1], &l_rem, &r_rem);

	// 재귀 함수를 호출하여 모든 가능한 유효한 문자열을 찾아 출력
	rip_recursive(av[1], 0, l_rem, r_rem);

	return 0;
}
