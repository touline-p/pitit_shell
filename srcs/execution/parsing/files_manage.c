/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_manage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:01:03 by twang             #+#    #+#             */
/*   Updated: 2023/04/05 17:57:24 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

/*---- prototypes ------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/

void	files_management(t_data *data, char *file, t_token_minishell token)
{
	if (token == CHEVRON_IN)
	{
		if (data->cmds_block->infile != 0)
			close(data->cmds_block->infile);
		data->cmds_block->infile = open(file, O_RDONLY, 0644);
		if (data->cmds_block->infile == -1)
			perror("open infile");
	}
	else 
	{
		if (data->cmds_block->outfile != 0)
			close(data->cmds_block->outfile);
		if (token == CHEVRON_OT)
			data->cmds_block->outfile = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			data->cmds_block->outfile = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (data->cmds_block->outfile == -1)
			perror("open outfile");
	}
}
