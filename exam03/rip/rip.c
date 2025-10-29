/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jaeholee <makest@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 11:35:21 by Jaeholee          #+#    #+#             */
/*   Updated: 2025/08/05 11:35:23 by Jaeholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int pcheck(int *check)
{
	int i = -1;
	while (++i < 4)
		printf("check[%d] : %d\n", i, check[i]);
	return (0);
}

int ft_strlen(char *string)
{
	int i = 0;
	while (string[i])
		i++;
	return (i);
}


int rip_space(char *pset, int *check, int ind)
{
	if (pset[ind] == '(')
		check[0] -= 1;
	else
		check[1] -= 1;
	check[2] -= 1;
	pset[ind] = ' ';
	return (0);
}

int rip_rollback(char *pset, int *check, int ind, char save)
{
	pset[ind] = save;
	if (save == '(')
		check[0] += 1;
	else
		check[1] += 1;
	check[2] += 1;
	return (0);
}

int rip_state(char *pset, int *check)
{
	int i = 0;
	int end = ft_strlen(pset) - 1;
	while (pset[i] == ')')
		pset[i++] = ' ';
	while (end >= 0 && pset[end] == '(')
	{
		pset[end] = ' ';
		end--;
	}
	while (pset[i])
	{
		if (pset[i] == '(')
			check[0] += 1;
		else if (pset[i] == ')')
		{
			if (check[0] > 0)
				check[0] -= 1;
			else		
				check[1] += 1;
		}
		i++;
	}
	check[2] = check[0] + check[1];
	return (0); 
}

int pset_check(char *pset)
{
	int i = 0;
	int sum = 0;
	//int signal = 1;
	while (pset[i])
	{
		if (pset[i] == '(')
		{
			sum += 1;
			//signal = 0;
		}
		else if (pset[i] == ')')
		{
			sum -= 1;
			//signal = 0;
		}
		if (sum < 0)
			return (0);
		i++;
	}
	return (sum == 0);
}

int rip_skip_check(char *pset, int *check, int ind)
{
	if (pset[ind] == '(')
	{
		if (check[0] > 0)
			return (0);
	}
	if (pset[ind] == ')')
	{
		if (check[1] > 0)
			return (0);
	}
	return (1);
}

int rip(char *pset, int *check, int ind)
{
	if (!check[2])
	{
		if (pset_check(pset))
			puts(pset);
		return (0);
	}
	int i = ind;
	char save = 0;
	while (pset[i])
	{
		if (rip_skip_check(pset, check, i))
		{
			i++;
			continue ;
		}
		save = pset[i];
		rip_space(pset, check, i);
		rip(pset, check, i + 1);
		rip_rollback(pset, check, i, save);
		i++;
	}
	return (0);
}

int main(int ac, char **av)
{
	(void) ac;
	int check[3] = {0};
	rip_state(av[1], check);
	//pcheck(check);
	rip(av[1], check, 0);
	return (0);
}










































