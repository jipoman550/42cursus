/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:35:15 by sisung            #+#    #+#             */
/*   Updated: 2026/02/02 19:23:45 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	collect_arg_list(t_cmd *cmd, t_list **arg_list, t_shell *sh)
{
	int		i;
	char	*expanded;

	i = 0;
	while (cmd->argv[i])
	{
		expanded = expand_str(cmd->argv[i], sh);
		split_argv_by_space(arg_list, expanded);
		free(expanded);
		i++;
	}
}

static int	process_cmd_argv(t_cmd *cmd, t_shell *sh)
{
	t_list	*arg_list;
	char	**new_argv;

	arg_list = NULL;
	collect_arg_list(cmd, &arg_list, sh);
	remove_quotes_from_list(arg_list);
	new_argv = convert_list_to_argv(arg_list);
	if (!new_argv)
	{
		ft_lstclear(&arg_list, free);
		return (-1);
	}
	free_str_array(cmd->argv);
	cmd->argv = new_argv;
	ft_lstclear(&arg_list, free);
	return (0);
}

static int	expand_cmd_node(t_cmd *cmd, t_shell *sh)
{
	if (process_cmd_argv(cmd, sh) == -1)
		return (-1);
	expand_redirections(cmd, sh);
	return (0);
}

int	run_expander(t_pipeline *pipeline, t_shell *sh)
{
	t_cmd	*curr;

	if (!pipeline || !pipeline->cmds)
		return (0);
	curr = pipeline->cmds;
	while (curr)
	{
		if (expand_cmd_node(curr, sh) == -1)
			return (1);
		curr = curr->next;
	}
	return (0);
}
