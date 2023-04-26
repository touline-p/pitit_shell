/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switchman_once.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:58:48 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/04/26 22:58:49 by bpoumeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by bpoumeau on 4/22/23.
//

#include "../../incs/execution_incs/minishell_execution.h"
#include "../../incs/parsing_incs/minishell_parsing.h"

t_return_status	switchman_once(t_data *data, char ***env_pt)
{
	int		pid;
	t_cmd	*cmd;

	cmd = data->cmds_block;
	if (cmd->id_command > PWD
		|| (cmd->id_command == EXPORT && cmd->commands[1] != NULL))
		return (builtin_switch(cmd->id_command, cmd->commands, env_pt));
	pid = fork();
	if (pid == 0)
	{
		duplicate_fds(data, 0);
		builtin_switch(cmd->id_command, cmd->commands, env_pt);
		exit(g_ret_val);
	}
	return (SUCCESS);
}
