/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 10:27:15 by twang             #+#    #+#             */
/*   Updated: 2023/04/24 12:42:08 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell_execution.h"

void	check_opened_infiles(t_data *data, int block_id)
{
	if (data->cmds_block[block_id].infile > 2)
		close(data->cmds_block[block_id].infile);
}

void	check_opened_outfiles(t_data *data, int block_id)
{
	if (data->cmds_block[block_id].outfile > 2) {
		close(data->cmds_block[block_id].outfile);
	}
}