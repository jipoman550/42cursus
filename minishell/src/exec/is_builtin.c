/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hama <hama@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:32:12 by hama              #+#    #+#             */
/*   Updated: 2026/02/03 16:42:55 by hama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "exec.h"

int	is_builtin(const char *str)
{
	if (!str)
		return (0);
	if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "cd"))
		return (1);
	if (!ft_strcmp(str, "pwd") || !ft_strcmp(str, "export"))
		return (1);
	if (!ft_strcmp(str, "unset") || !ft_strcmp(str, "env"))
		return (1);
	if (!ft_strcmp(str, "exit"))
		return (1);
	return (0);
}

int	is_par_builtin(const char *str)
{
	if (!str)
		return (0);
	if (!ft_strcmp(str, "cd"))
		return (1);
	if (!ft_strcmp(str, "export"))
		return (1);
	if (!ft_strcmp(str, "unset"))
		return (1);
	if (!ft_strcmp(str, "exit"))
		return (1);
	return (0);
}
