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

static t_return_status	_execute_son(t_data *data, t_cmd cmd, char ***env_pt)
{
	free(data->cmds_block);
	free(data->prompt);
	ft_free_all_str_lst(data, data->index);
	if (duplicate_fds(cmd, data, env_pt) != SUCCESS) {
		ft_free_split(cmd.commands);
		ft_free_split(*env_pt);
		g_ret_val = 1;
		exit(1);
	}
	builtin_switch(cmd, cmd.commands, env_pt);
	ft_free_split(*env_pt);
	if (cmd.id_command != EXPORT)
		ft_free_split(cmd.commands);
	else
	{
		free(*(cmd.commands));
		free(cmd.commands);
	}
	exit(SUCCESS);
}

void	close_switchman_once(t_cmd cmd)
{
	if (cmd.infile > 2)
		close(cmd.infile);
	if (cmd.outfile > 2)
		close(cmd.outfile);
}

t_return_status	switchman_once(t_data *data, char ***env_pt)
{
	int		pid;
	int		status;
	t_cmd	cmd;

	status = 0;
	cmd = *(data->cmds_block);
	if (cmd.id_command > PWD
		|| (cmd.id_command == EXPORT && cmd.commands[1] != NULL))
		return (builtin_switch(cmd, cmd.commands, env_pt));
	pid = fork();
	if (pid == 0)
		_execute_son(data, cmd, env_pt);
	ft_free_split(cmd.commands);
	close_switchman_once(cmd);
	if (waitpid(pid, &status, WUNTRACED) == -1) {
		g_ret_val = 1;
	}
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
