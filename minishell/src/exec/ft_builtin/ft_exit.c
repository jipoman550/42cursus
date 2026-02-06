/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hama <hama@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 09:59:24 by hama              #+#    #+#             */
/*   Updated: 2026/02/05 20:01:49 by hama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "exec.h"

static int	is_num(const char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	print_too_args(t_shell *sh)
{
	ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
	sh->last_status = 1;
	sh->should_exit = 0;
	return (1);
}

static int	print_not_num(t_cmd *cmd, t_shell *sh)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(cmd->argv[1], STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	sh->last_status = 2;
	sh->should_exit = 1;
	return (2);
}

int	ft_exit(t_cmd *cmd, t_shell *sh)
{
	long	exit_code;

	if (!sh)
		return (1);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (!cmd->argv[1])
	{
		sh->should_exit = 1;
		return (sh->last_status);
	}
	if (!is_num(cmd->argv[1]))
		print_not_num(cmd, sh);
	else if (cmd->argv[2])
		return (print_too_args(sh));
	exit_code = ft_atoi(cmd->argv[1]);
	sh->last_status = (unsigned char)exit_code;
	sh->should_exit = 1;
	return (sh->last_status);
}
