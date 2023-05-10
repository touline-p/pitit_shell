//
// Created by bpoumeau on 5/10/23.
//

#include "minishell_execution.h"
#include "../../incs/parsing_incs/minishell_parsing.h"

static void				_get_heredoc(char *limiter, int do_expand, int *fd_hd, char **env, t_data *data);
static t_return_status	_get_here_doc_in_hr_data(t_data *data, t_string_token *token, char **env);
static void				_trim_limiter(char *s);
static t_return_status	_expand_hd(char **here_doc, char **env);

void reset_booleans(bool *a, t_pr_stat *b)
{
	*a = false;
	*b = NO_PAR;
}

t_return_status heredoc_management(t_data *data, t_string_token *string_token_lst, char **env)
{
	t_string_token	*tmp;

	tmp = string_token_lst;
	update_tokens(string_token_lst);
	/*
	while (tmp != NULL)
	{
		if (tmp->token == HERE_DOC)
		{
			tmp = tmp->next;
			if (_get_here_doc_in_hr_data(data, tmp, env) != SUCCESS)
				return (FAILED_MALLOC);
		}
		tmp = tmp->next;
	}
	 */
	return (SUCCESS);
}

static t_return_status	_get_here_doc_in_hr_data(t_data *data, t_string_token *token, char **env)
{
	char	*limiter;
	int 	fd_hd[2];
	bool	do_expand;
	int 	pid;
	int 	status;

	token->token = HR_DATA;
	limiter = token->content;
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
		free(data->prompt);
		free(data->cmds_block);
		signal(SIGINT, &handle_signal_heredoc);
		signal(SIGQUIT, &handle_signal_heredoc);
		_get_heredoc(limiter, do_expand, fd_hd, env, data);
	}
	else
	{
		close(fd_hd[1]);
		printf("i do herdoc for %s\n", limiter);
		if (read_fd_in_str(fd_hd[0], &(token->content)) != SUCCESS)
			return (FAILED_MALLOC);
		if (waitpid(pid,  &status, WUNTRACED) == -1)
			g_ret_val = WEXITSTATUS(status);
		else if (WIFEXITED(status))
			g_ret_val = WEXITSTATUS(status);
	}
	if (g_ret_val == 130)
		return (FAILURE);
	return (SUCCESS);
}

static void	_get_heredoc(char *limiter, int do_expand, int *fd_hd, char **env, t_data *data)
{
	char	*line;
	char	*here_doc;
	int		nb_of_line;

	line = NULL;
	here_doc = NULL;
	here_doc = ft_strdup("");
	if (!here_doc)
		perror("here doc _get_heredoc");
	nb_of_line = 0;
	while (HEREDOC_MUST_GO_ON)
	{
		nb_of_line++;
		ft_dprintf(2, GREEN"> "END);
		line = get_next_line(0);
		if (!line)
		{
			ft_dprintf(2, RED"minishell: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n"END, nb_of_line, limiter);
			break ;
		}
		*ft_strchr(line, '\n') = 0;
		if (!ft_strncmp(limiter, line, ft_strlen(limiter) + 1))
			break;
		*ft_strchr(line, '\0') = '\n';
		here_doc = strjoin_path_cmd(here_doc, line);
		free(line);
	}
	get_next_line(-1);
	free(line);
	if (do_expand == false)
		_expand_hd(&here_doc, env);
	ft_free_split(env);
	if (here_doc)
		write(fd_hd[1], here_doc, ft_strlen(here_doc));
	close(fd_hd[0]);
	close(fd_hd[1]);
	free(here_doc);
	string_token_destructor(data->instructions_arr[data->index]);
	ft_free_all_str_lst(data, data->index);
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
