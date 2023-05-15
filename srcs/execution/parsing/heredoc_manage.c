//
// Created by bpoumeau on 5/10/23.
//

#include "minishell_execution.h"
#include "../../incs/parsing_incs/minishell_parsing.h"

static void				_get_heredoc(char *limiter, int do_expand, int *fd_hd, char **env);
static t_return_status	_get_here_doc_in_hr_data(t_data *data, t_string_token *token, char **env);
static void				_trim_limiter(char *s);
static t_return_status	_expand_hd(char **here_doc, char **env);

void reset_booleans(bool *a, t_pr_stat *b)
{
	*a = false;
	*b = NO_PAR;
}

static t_return_status 	check_closing_par(t_string_token *string_token_lst)
{
	int open_par;

	open_par = 0;
	while (string_token_lst->next != NULL)
	{
		if (string_token_lst->token == O_PRTSS)
			open_par++;
		else if (string_token_lst->token == C_PRTSS)
		{
			open_par--;
			if (open_par < 0)
			{
				string_token_lst->token = SYN_ERR;
				return (FAILURE);
			}
		}
		string_token_lst = string_token_lst->next;
	}
	if (open_par > 0)
	{
		string_token_lst->token = SYN_ERR;
		return (FAILURE);
	}
	return (SUCCESS);
}

t_return_status heredoc_management(t_data *data, t_string_token *string_token_lst, char **env)
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
			redirection_syntax_error(format_string_token(tmp->next));
			return (FAILURE);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

static t_return_status	_get_here_doc_in_hr_data(t_data *data, t_string_token *token, char **env)
{
	char	*limiter;
	int 	fd_hd[2];
	bool	do_expand;
	int 	pid;
	int 	status;

	do_expand = false;
	limiter = token->content;
	token->content = NULL;
	if (ft_strchr(limiter, -'\'') || ft_strchr(limiter, -'\"'))
	{
		do_expand = true;
		_trim_limiter(limiter);
	}
	if (pipe(fd_hd) == -1)
		return (FAILED_PIPE);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		string_token_destructor(data->instructions_arr[0]);
		free(data->instructions_arr);
		free(data->prompt);
		signal(SIGINT, &handle_signal_heredoc);
		signal(SIGQUIT, &handle_signal_heredoc);
		_get_heredoc(limiter, do_expand, fd_hd, env);
	}
	else
	{
		free(limiter);
		close(fd_hd[1]);
		if (read_fd_in_str(fd_hd[0], &(token->content)) != SUCCESS)
			return (FAILED_MALLOC);
		close(fd_hd[0]);
		if (waitpid(pid,  &status, WUNTRACED) == -1)
			g_ret_val = WEXITSTATUS(status);
	}
	if (g_ret_val == 130)
		return (FAILURE);
	return (SUCCESS);
}

static bool	_read_hd_ep(char *line, int nb_of_line, char *limiter)
{
	if (errno)
	{
		perror("here doc gnl");
		perror("here doc get next line");
		return (true);
	}
	if (!line)
	{
		ft_dprintf(2, RED"minishell: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n"END, nb_of_line, limiter);
		return (true);
	}
	return (false);
}

t_return_status	read_here_doc_in_str(char *limiter, char **documentation)
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
		if (_read_hd_ep(line, nb_of_line, limiter))
			break ;
		if (!ft_strncmp(limiter, line, ft_strlen(limiter) + 1))
			break;
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

static void	_get_heredoc(char *limiter, int do_expand, int *fd_hd, char **env)
{
	char	*line;
	char	*here_doc;

	line = NULL;
	here_doc = NULL;
	here_doc = ft_strdup("");
	if (!here_doc)
		perror("here doc _get_heredoc");
	read_here_doc_in_str(limiter, &here_doc);
	get_next_line(-1);
	free(line);
	free(limiter);
	if (do_expand == false)
		_expand_hd(&here_doc, env);
	ft_free_split(env);
	if (here_doc)
		write(fd_hd[1], here_doc, ft_strlen(here_doc));
	close(fd_hd[0]);
	close(fd_hd[1]);
	free(here_doc);
	exit(g_ret_val);
}

static t_return_status _expand_hd(char **here_doc, char **env)
{
	char	**arr;

	if (cut_line_on(*here_doc, &arr) != SUCCESS
		|| join_arr_on(arr, here_doc, env) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

static void	_trim_limiter(char *s)
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
