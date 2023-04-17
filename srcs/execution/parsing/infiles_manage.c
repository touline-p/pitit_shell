/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infiles_manage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:01:03 by twang             #+#    #+#             */
/*   Updated: 2023/04/17 19:21:32 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

/*---- prototypes ------------------------------------------------------------*/

static void	set_infile(t_data *data, char *file, int cmd_block_id);
static t_return_status	set_heredoc(t_data *data, char *limiter, int block_id);
static void	get_heredoc(t_data *data, char *limiter, int block_id);

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
	check_opened_files(data, block_id);
	data->cmds_block[block_id].infile = open(file, O_RDONLY, 0644);
	if (data->cmds_block[block_id].infile == -1)
		perror("open infile");
}

static t_return_status	set_heredoc(t_data *data, char *limiter, int block_id)
{
	check_opened_files(data, block_id);
	data->cmds_block[block_id].is_heredoc = true;
	if (pipe(data->cmds_block[block_id].fd) == -1)
		return (FAILED_PIPE);
	data->cmds_block[block_id].process_id = fork();
	if (data->cmds_block[block_id].process_id == 0)
	{
		get_heredoc(data, limiter, block_id);
	}
	else
		waitpid(data->cmds_block[block_id].process_id, NULL, 0);
	return (SUCCESS);
}

static void	get_heredoc(t_data *data, char *limiter, int block_id)
{
	char	*line;
	char	*here_doc;
	bool	do_expand;
	
	line = NULL;
	here_doc = NULL;
	do_expand = false;
	if (strchr(limiter, -'\'') || strchr(limiter, -'\"'))
		do_expand = true;
	while (HEREDOC_MUST_GO_ON)
	{
		ft_dprintf(2, GREEN"> "END);
		line = get_next_line(0);
		if (!line)
		{
			ft_dprintf(2, "\n");
			break ;
		}
		if (!ft_strncmp(limiter, line, ft_strlen(line) - 1))
			break ;
		here_doc = strjoin_path_cmd(here_doc, line);
	}
	free(line);
	if (do_expand == true)
	{
		puts("je ne fais pas de expand!");
		/*here_doc = la fonction expand du Beau Brieuc*/
	}
	if (here_doc)
		write(data->cmds_block[block_id].fd[1], here_doc, ft_strlen(here_doc));
	close(data->cmds_block[block_id].fd[1]);
	// printf(GREEN"%s"END, here_doc);
	free(here_doc);
}