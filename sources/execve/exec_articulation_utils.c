/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_articulation_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangthea <wangthea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:54:36 by wangthea          #+#    #+#             */
/*   Updated: 2023/05/19 15:50:47 by wangthea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_cmd(t_cmd *cmd)
{
	while (cmd->commands)
	{
		if (cmd->infile == -1 && cmd->is_heredoc == true)
			return (true);
		cmd++;
	}
	return (false);
}

void	init_data(t_data *data)
{
	data->cmds_block = NULL;
	data->fd[0] = 0;
	data->fd[1] = 0;
	data->nb_of_pipe = 0;
}
