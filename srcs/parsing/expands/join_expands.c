//
// Created by bpoumeau on 4/3/23.
//
#include "../../../libft/libft.h"
#include "../../../incs/parsing_incs/minishell_parsing.h"

static t_return_status 	_expand_lines(char **str_arr, char **env);
static void 			_remove_quotes(char **str_arr);

t_return_status	join_arr_on(char **str_arr, char **line_pt, char **env)
{
	if (_expand_lines(str_arr, env) != SUCCESS)
		return (ft_free_split(str_arr), SUCCESS);
	_remove_quotes(str_arr);
	if (ft_join_str_arr_on(str_arr, line_pt) != SUCCESS)
		return (ft_free_split(str_arr), FAILED_MALLOC);
	return (ft_free_split(str_arr), SUCCESS);
}

static t_return_status 	_expand_lines(char **str_arr, char **env)
{
	while (*str_arr)
	{
		if (**str_arr == - '"' \
			&& replace_dquotes_str_by_env_value(str_arr, env) != SUCCESS)
			return (FAILED_MALLOC);
		else if (**str_arr == '$' \
			&& replace_dollar_str_by_env_value(str_arr, env) != SUCCESS)
			return (FAILED_MALLOC);
		str_arr++;
	}
	return (SUCCESS);
}

void cpy_next_char(unsigned int index, char *str)
{
	(void)index;
	*str = *(str + 1);
	if (*str == - '\'' || *str == - '"')
		*str = 0;
}

static void	_remove_quotes(char **str_arr)
{
	const char	quotes_arr[] = {- '\'', - '"', 0};

	while (*str_arr)
	{
		if (is_from(**str_arr, (char *)quotes_arr))
			ft_striteri(*str_arr, &cpy_next_char);
		str_arr++;
	}
}

//#define TST_JOIN_EXP

#ifdef TST_JOIN_EXP

#include <stdio.h>

void change(char *line)
{
	while (*line)
	{
		if (is_from(*line, "'\""))
			*line = -(*line);
		line++;
	}
}

int main(int ac, char **av, char **env)
{
	(void)ac; (void)av; (void)env;

	t_string_token 	*tok_lst;
	char	*line = ft_strdup("expand\"qui\"\"\" \'marche\'$USER ");
	get_lexed_str_token_lst_from_line(line, &tok_lst, env);
	cut_all_lines(tok_lst);
	join_all_lines(tok_lst, env);
	display_str_token(tok_lst);
	string_token_destructor(tok_lst);
}

#endif