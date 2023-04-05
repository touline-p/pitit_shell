/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_manage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 18:58:11 by twang             #+#    #+#             */
/*   Updated: 2023/04/05 17:56:48 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

/*---- prototypes ------------------------------------------------------------*/



/*----------------------------------------------------------------------------*/

void	heredoc_management(t_data *data, char *limiter)
{
	int		fd[2];
	char	*line;
	
	if (data->cmds_block->infile != 0)
			close(data->cmds_block->infile);
	if (pipe(fd) == -1)
		exit(dprintf(2, RED"Error\nPipe Issue\n"END));
	else if (pipe(fd) == 0)
	{
		while (HEREDOC_MUST_GO_ON)
		{
			line = readline(PURPLE"> "END);
			if (!strcmp(line, limiter))
			{
				free(limiter);
				break ;
			}
			write(fd[1], line, ft_strlen(line));
			free(line);
		}
	}
	if (line)
	{
		free(line);
		line = NULL;
	}
}
