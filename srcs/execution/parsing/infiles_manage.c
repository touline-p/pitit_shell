/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infiles_manage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangthea <wangthea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:01:03 by twang             #+#    #+#             */
/*   Updated: 2023/04/06 23:37:11 by wangthea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

/*---- prototypes ------------------------------------------------------------*/

static void	set_infile(t_data *data, char *file, int cmd_block_id);
static void	set_heredoc(t_data *data, char *file, int cmd_block_id);

/*----------------------------------------------------------------------------*/

void	infiles_management(t_data *data, t_string_token *string_of_tokens)
{
	int				i;
	t_string_token	*temp;

	i = 0;
	temp = string_of_tokens;
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
	/*open pipe, fork, strjoin -> creer t'on un fichier temp ou on join tout 
	dans le pipe ?*/
}
