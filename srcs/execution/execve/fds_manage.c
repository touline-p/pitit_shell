/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:26:01 by twang             #+#    #+#             */
/*   Updated: 2023/04/17 19:34:12 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

void	close_fds(t_data *data, int block_id)
{
	int	i;

	i = 0;
	while (i < data->nb_of_pipe)
	{
		if (i != block_id - 1)
			close(data->cmds_block[block_id].fd);
		if (i != block_id)
			close(data->cmds_block[block_id].fd);
		i++;
	}
}

void	close_all_fds(t_data *data, int block_id)
{
	int	i;

	i = 0;
	while (i < block_id)
	{
		close(data->cmds_block[block_id].fd[0]);
		close(data->cmds_block[block_id].fd[1]);
		i++;
	}
}

static void	duplicate_fds(t_data *data, int block_id)
{
	if (block_id == 0)
	{
		if (dup2(data->cmds_block[block_id].infile, STDIN_FILENO) == -1)
			exit(3);
		close(data->cmds_block[block_id].infile);
	}
	else
	{
		if (dup2(data->cmds_block[block_id - 1].fd[0], STDIN_FILENO) == -1)
			exit(3);
		close(data->cmds_block[block_id - 1].fd[0]);
	}
	if (block_id == data->nb_of_pipe)
	{
		if (dup2(data->cmds_block[block_id].outfile, STDOUT_FILENO) == -1)
			exit(3);
		close(data->cmds_block[block_id].outfile);
	}
	else
	{
		if (data->cmds_block[block_id - 1].fd[1], STDOUT_FILENO) == -1)
			exit(3);
		close(data->cmds_block[block_id - 1].fd[1]);
	}
}

