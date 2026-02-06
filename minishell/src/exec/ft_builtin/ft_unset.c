/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hama <hama@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 09:59:10 by hama              #+#    #+#             */
/*   Updated: 2026/02/04 18:59:25 by hama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "parser.h"

int	ft_unset(t_cmd *cmd, t_shell *sh)
{
	int	i;
	int	result;

	if (!sh || !sh->envp)
		return (1);
	result = 0;
	i = 1;
	while (cmd->argv[i])
	{
		if (!valid_key(cmd->argv[i]))
			result = 0;
		else
			env_unset(&sh->envp, cmd->argv[i]);
		i++;
	}
	return (result);
}
