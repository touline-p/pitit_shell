/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 18:35:20 by twang             #+#    #+#             */
/*   Updated: 2023/05/21 20:48:43 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*---- prototypes ------------------------------------------------------------*/

static t_return_status	_get_here_doc_in_hr_data(t_data *data, \
											t_string_token *token, char **env);
static t_return_status	_father_process_here_doc_reading(char *limiter, \
											int *fd_hd, char **dst, int pid);
static void				_get_heredoc(char *limiter, int do_expand, int *fd_hd, \
											char **env);
static t_return_status	_read_here_doc_in_str(char *limiter, \
											char **documentation);

/*----------------------------------------------------------------------------*/

t_return_status	heredoc_management(t_data *data, \
								t_string_token *string_token_lst, char **env)
{
	t_string_token	*tmp;

	tmp = string_token_lst;
	update_tokens(string_token_lst);
	if (check_closing_par(string_token_lst) == FAILURE)
		check_par_err(string_token_lst);
	while (tmp != NULL)
	{
		if (tmp->token == HR_DATA)
		{
			if (_get_here_doc_in_hr_data(data, tmp, env) != SUCCESS)
				return (FAILED_MALLOC);
		}
		if (tmp->token == SYN_ERR)
		{
			if (redirection_syntax_error(format_string_token(tmp->next)) != SUCCESS)
			{
				string_token_destructor(string_token_lst);
				free(data->instructions_arr);
			}
			return (FAILURE);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

//// proteger TO DO
static t_return_status	_get_here_doc_in_hr_data(t_data *data, \
											t_string_token *token, char **env)
{
	char	*limiter;
	int		fd_hd[2];
	bool	do_expand;
	int		pid;

	if (set_up_get_here_doc(token, &limiter, &do_expand, fd_hd))
		return (FAILED_PIPE);
	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		get_heredoc_setup(data);
		_get_heredoc(limiter, do_expand, fd_hd, env);
	}
	else
	{
		if (_father_process_here_doc_reading(limiter, fd_hd, \
			&(token->content), pid) != SUCCESS)
			return (FAILURE);
	}
	if (g_ret_val == 130)
		return (FAILURE);
	return (SUCCESS);
}

static t_return_status	_father_process_here_doc_reading(char *limiter, \
				int *fd_hd, char **dst, int pid)
{
	int	status;

	free(limiter);
	close(fd_hd[1]);
	if (read_fd_in_str(fd_hd[0], dst) != SUCCESS)
		return (FAILED_MALLOC);
	close(fd_hd[0]);
	if (waitpid(pid, &status, WUNTRACED) == -1)
		g_ret_val = WEXITSTATUS(status);
	else if (WIFEXITED(status))
		g_ret_val = WEXITSTATUS(status);;
	return (SUCCESS);
}

static void	_get_heredoc(char *limiter, int do_expand, int *fd_hd, char **env)
{
	char	*line;
	char	*here_doc;

	line = NULL;
	here_doc = NULL;
	here_doc = ft_strdup("");
	if (!here_doc)
		perror("here doc _get_heredoc");
	_read_here_doc_in_str(limiter, &here_doc);
	free(line);
	free(limiter);
	if (do_expand == false)
		expand_hd(&here_doc, env);
	ft_free_split(env);
	if (here_doc)
		write(fd_hd[1], here_doc, ft_strlen(here_doc));
	close(fd_hd[0]);
	close(fd_hd[1]);
	free(here_doc);
	exit(g_ret_val);
}

static t_return_status	_read_here_doc_in_str(char *limiter, \
												char **documentation)
{
	int		nb_of_line;
	char	*line;

	nb_of_line = 0;
	line = NULL;
	errno = 0;
	while (HEREDOC_MUST_GO_ON)
	{
		nb_of_line++;
		line = readline(GREEN"> "END);
		if (read_hd_ep(line, nb_of_line, limiter))
			break ;
		if (!ft_strncmp(limiter, line, ft_strlen(limiter) + 1))
			break ;
		if (*documentation == NULL)
			break ;
		*documentation = strjoin_path_cmd(*documentation, line);
		*documentation = ft_strjoin_free_first_sf(*documentation, "\n");
		if (*documentation == NULL)
			free(line);
	}
	if (errno)
		return (FAILURE);
	return (SUCCESS);
}
