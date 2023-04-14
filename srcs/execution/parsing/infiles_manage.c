/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infiles_manage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:01:03 by twang             #+#    #+#             */
/*   Updated: 2023/04/14 17:13:02 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

/*---- prototypes ------------------------------------------------------------*/

static void	set_infile(t_data *data, char *file, int cmd_block_id);
static t_return_status	set_heredoc(t_data *data, char *limiter, int block_id);

/*----------------------------------------------------------------------------*/

void	infiles_management(t_data *data, t_string_token *lst_of_tok)
{
	int				i;
	t_string_token	*temp;

	i = 0;
	temp = lst_of_tok;
	while (temp != NULL)
	{
		if (temp->token == CHEVRON_IN)
		{
			temp = temp->next;
			set_infile(data, temp->content, i);
		}
		if (temp->token == HERE_DOC)
		{
			temp = temp->next;
			set_heredoc(data, temp->content, i);
		}
		if (temp->token == PIPE)
		{
			i++;
		}
		temp = temp->next;
	}
}

static void	set_infile(t_data *data, char *file, int block_id)
{
	if (data->cmds_block[block_id].infile != 0)
		close(data->cmds_block[block_id].infile);
	data->cmds_block[block_id].infile = open(file, O_RDONLY, 0644);
	if (data->cmds_block[block_id].infile == -1)
		perror("open infile");
}

static t_return_status	set_heredoc(t_data *data, char *limiter, int block_id)
{
	char	*line;
	
	if (data->cmds_block[block_id].infile != 0)
		close(data->cmds_block[block_id].infile);
	if (pipe(data->cmds_block[block_id].fd) == -1)
		return (FAILED_PIPE);
	line = NULL;
	data->cmds_block[block_id].process_ids = fork();
	if (data->cmds_block[block_id].process_ids == 0)
	{
		while (HEREDOC_MUST_GO_ON)
		{
			dprintf(1, GREEN"> "END);
			line = get_next_line(0);
			if (!line)
				break ;
			if (!ft_strncmp(limiter, line, ft_strlen(line) - 1))
				break ;
			free(line);
		}
	}
	else
		waitpid(data->cmds_block[block_id].process_ids, NULL, 0);
	return (SUCCESS);
	/*
		- open pipe
		- fork
		- remplir char  -> get_next_line
		- launch expand
		- put char * in pipe
		- infile = 3 [if infile == 3 -> close[fd pipe] ET free char *heredoc?]
		- check : if (line == NULL) || if (found LIMITER) --> break
		- else : ft_dprintf(fd, line); ft_dprintf("\n");
		
		L'HISTORIQUE DU HEREDOC ??
		
	*/
}
