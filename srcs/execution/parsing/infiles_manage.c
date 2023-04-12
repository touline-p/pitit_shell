/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infiles_manage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:01:03 by twang             #+#    #+#             */
/*   Updated: 2023/04/12 14:32:27 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

/*---- prototypes ------------------------------------------------------------*/

static void	set_infile(t_data *data, char *file, int cmd_block_id);
static void	set_heredoc(t_data *data, char *file, int cmd_block_id);

/*----------------------------------------------------------------------------*/

void	infiles_management(t_data *data, t_string_token *str_of_tok)
{
	int				i;
	t_string_token	*temp;

	i = 0;
	temp = str_of_tok;
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

static void	set_heredoc(t_data *data, char *file, int block_id)
{
	(void)data;
	(void)file;
	(void)block_id;
	puts("we have to set the heredoc");
	/*
		- open pipe
		- fork
		- remplir char  -> get_next_line
		- launch expand
		- put char * in pipe
		- infile = 3 [if infile == 3 -> close[fd pipe] ET free char *heredoc?]
		- check : if (line == NULL) || if (found LIMITER) --> break
		- else : ft_dprintf(fd, line); ft_dprintf("\n");
	*/
}
