/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infiles_manage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:01:03 by twang             #+#    #+#             */
/*   Updated: 2023/04/24 17:19:28 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

/*---- prototypes ------------------------------------------------------------*/

static void				set_infile(t_data *data, char *file, int cmd_block_id, char **env);
static t_return_status	set_heredoc(t_data *data, char *limiter, int block_id, char **env);
static void				get_heredoc(char *limiter, int do_expand, int *fd_hd, char **env);
static void				trim_limiter(char *s);

/*----------------------------------------------------------------------------*/

void	infiles_management(t_data *data, t_string_token *lst_of_tok, char **env)
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
			set_infile(data, temp->content, i, env);
		}
		if (temp->token == HERE_DOC)
		{
			temp = temp->next;
			set_heredoc(data, temp->content, i, env);
		}
		if (temp->token == PIPE)
		{
			i++;
		}
		temp = temp->next;
	}
}

#include "../../incs/parsing_incs/minishell_parsing.h"

static void	set_infile(t_data *data, char *file, int block_id, char **env)
{
	char **arr;

	check_opened_infiles(data, block_id);
	cut_line_on(file, &arr);
	join_arr_on(arr, &file, env);
	if (ft_strchr(file, -32) != NULL)
	{
		data->cmds_block[block_id].infile = -1;
		data->cmds_block[block_id].is_ambiguous = true;
		return ;
	}
	data->cmds_block[block_id].infile = open(file, O_RDONLY, 0644);
	if (data->cmds_block[block_id].infile == -1)
		perror("open infile");
}

static t_return_status	set_heredoc(t_data *data, char *limiter, int block_id, char **env)
{
	int 	fd_hd[2];
	bool	do_expand;

	do_expand = false;
	check_opened_infiles(data, block_id);
	data->cmds_block[block_id].is_heredoc = true;
	if (ft_strchr(limiter, -'\'') || ft_strchr(limiter, -'\"'))
	{
		do_expand = true;
		trim_limiter(limiter);
	}
	if (pipe(fd_hd) == -1)
		return (FAILED_PIPE);
	signal(SIGINT, SIG_IGN);
	data->cmds_block[block_id].process_id = fork();
	if (data->cmds_block[block_id].process_id == 0)
	{
		signal(SIGINT, &handle_signal_heredoc);
		signal(SIGQUIT, &handle_signal_heredoc_sigquit);
		get_heredoc(limiter, do_expand, fd_hd, env);
	}
	else
	 {
		waitpid(data->cmds_block[block_id].process_id, &g_ret_val, 0);
		close(fd_hd[1]);
	 }
	data->cmds_block[block_id].infile = fd_hd[0];
	return (SUCCESS);
}

static t_return_status expand_hd(char **here_doc, char **env)
{
	char	**arr;

	if (cut_line_on(*here_doc, &arr) != SUCCESS
		|| join_arr_on(arr, here_doc, env) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

static void	get_heredoc(char *limiter, int do_expand, int *fd_hd, char **env)
{
	char	*line;
	char	*here_doc;
	
	line = NULL;
	here_doc = NULL;
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
		{
			break;
		}
		here_doc = strjoin_path_cmd(here_doc, line);
		free(line);
	}
	free(line);
	if (do_expand == false)
		expand_hd(&here_doc, env);
	if (here_doc)
		write(fd_hd[1], here_doc, ft_strlen(here_doc));
	close(fd_hd[0]);
	close(fd_hd[1]);
	free(here_doc);
	exit(EXIT_SUCCESS);
}

static void	trim_limiter(char *s)
{
	while (*s)
	{
		while (*s && (*s != -'\'' && *s != -'\"'))
			s++;
		if (*s == '\0')
			break ;
		ft_memmove(s, s + 1, ft_strlen(s));
	}
}