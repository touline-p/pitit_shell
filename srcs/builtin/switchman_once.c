/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switchman_once.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:58:48 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/05/05 14:18:42 by twang            ###   ########.fr       */
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
	int		status;
	t_cmd	cmd;

	status = 0;
	cmd = *(data->cmds_block);
	if (cmd.id_command > PWD
		|| (cmd.id_command == EXPORT && cmd.commands[1] != NULL))
		return (builtin_switch(cmd.id_command, cmd.commands, env_pt));
	pid = fork();
	if (pid == 0)
	{
		free(data->prompt);
		free(data->cmds_block);
		if (duplicate_fds(cmd) != SUCCESS)
		{
			ft_free_split(cmd.commands);
			exit(1);
		}
		builtin_switch(cmd.id_command, cmd.commands, env_pt);
		g_ret_val = 0;
		exit(g_ret_val);
	}
	ft_free_split(cmd.commands);
	if (waitpid(pid, &status, WUNTRACED) == -1)
		g_ret_val = 1;
	else if (WIFEXITED(status))
		g_ret_val = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		g_ret_val = WTERMSIG(status);
		if (g_ret_val != 131)
			g_ret_val += 128;
	}
	return (SUCCESS);
}
