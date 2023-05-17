/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switchman_once.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:58:48 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/05/17 17:06:46 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*---- prototypes ------------------------------------------------------------*/

static t_return_status	_execute_son(t_data *data, t_cmd cmd, char ***env_pt);
static void				_close_switchman_once(t_cmd cmd);

/*----------------------------------------------------------------------------*/

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
	_close_switchman_once(cmd);
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

static t_return_status	_execute_son(t_data *data, t_cmd cmd, char ***env_pt)
{
	free(data->cmds_block);
	free(data->prompt);
	ft_free_all_str_lst(data, data->index);
	if (duplicate_fds(cmd, data, env_pt) != SUCCESS)
	{
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

static void	_close_switchman_once(t_cmd cmd)
{
	if (cmd.infile > 2)
		close(cmd.infile);
	if (cmd.outfile > 2)
		close(cmd.outfile);
}
