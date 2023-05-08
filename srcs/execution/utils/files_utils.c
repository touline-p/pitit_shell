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

bool file_is_empty(char *file)
{
	char *dup;
	char *dst;

	dup = ft_strdup(file);
	if (!dup) {
		perror("duplicating file");
		return true;
	}
	dst = ft_strchr(dup, -'"');
	while (dst)
	{
		ft_memmove(dst, dst + 1, ft_strlen(dst));
		dst = ft_strchr(dup, -'"');
	}
	dst = ft_strchr(dup, -'\'');
	while (dst)
	{
		ft_memmove(dst, dst + 1, ft_strlen(dst));
		dst = ft_strchr(dup, -'\'');
	}
	if (*dup)
		return (free(dup), true);
	free(dup);
	return (false);
}
