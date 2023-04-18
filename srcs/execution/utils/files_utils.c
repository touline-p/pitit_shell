/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangthea <wangthea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 10:27:15 by twang             #+#    #+#             */
/*   Updated: 2023/04/18 19:12:42 by wangthea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell_execution.h"

void	check_opened_infiles(t_data *data, int block_id)
{
	if (data->cmds_block[block_id].is_heredoc == true)
	{
		puts("faut liberer la chaine");
		data->cmds_block[block_id].is_heredoc = false;
	}
	if (data->cmds_block[block_id].fd[0] != 0)
		close(data->cmds_block[block_id].fd[0]);
	if (data->cmds_block[block_id].fd[1] != 0)
		close(data->cmds_block[block_id].fd[1]);
	if (data->cmds_block[block_id].infile != 0)
		close(data->cmds_block[block_id].infile);
}

void	check_opened_outfiles(t_data *data, int block_id)
{
	if (data->cmds_block[block_id].fd[0] != 0)
		close(data->cmds_block[block_id].fd[0]);
	if (data->cmds_block[block_id].fd[1] != 0)
		close(data->cmds_block[block_id].fd[1]);
	if (data->cmds_block[block_id].outfile != 0)
		close(data->cmds_block[block_id].outfile);
}