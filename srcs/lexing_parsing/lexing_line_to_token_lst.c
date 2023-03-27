//
// Created by bpoumeau on 3/15/23.
//

#include "minishell_parsing.h"
#include "structures_execution.h"

t_return_status	_syntax_is_valid_ep(t_emt token);
t_return_status	_check_meta(t_string_token *lst_to_check);
t_return_status is_a_meta(t_emt token);

t_string_token	*lexing_line_to_token_lst(char *line)
{
	t_string_token	*token_lst;
	t_token 		*basic_token_lst;

	token_lst = NULL;
	basic_token_lst = token_lst_constructor(line);
	if (basic_token_lst == NULL)
		return (NULL);
	preserve_token_lst(basic_token_lst);
	split_toklst_on_meta(basic_token_lst);
	regroup_meta(basic_token_lst);
	token_lst = token_lst_to_str_token(basic_token_lst);
	if (token_lst == NULL)
		return (NULL);
	del_space_token(token_lst);



	return (token_lst);
}

t_return_status	syntax_is_valid(t_string_token *lst_to_check)
{
	if (_check_meta(lst_to_check) != SUCCESS)
		//|| _check_redir(lst_to_check) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

t_return_status	_check_meta(t_string_token *lst_to_check)
{
	t_string_token	*pin;

	pin = lst_to_check;
	if (is_a_meta(pin->next->token) == SUCCESS)
		return (_syntax_is_valid_ep(pin->next->token));
	pin = pin->next;
	while (pin->token != EOL)
	{
		if (is_a_meta(pin->token) == SUCCESS && is_a_meta(pin->next->token) == SUCCESS)
			return (_syntax_is_valid_ep(pin->next->token));
		pin = pin->next;
	}
	return (SUCCESS);
}

t_return_status	_syntax_is_valid_ep(t_emt token)
{
	const char	str_arr[9][20] = {"'|'", "'||'", "'&&'", "'&'", "'>'", "'<'", "'>>'", "'<<'", "'newline'"};
	const t_emt	token_arr[] = {PIPE, OR, AND, AMPERSAND, CHEVRON_OT, CHEVRON_IN, APPENDS, HERE_DOC, EOL};
	size_t		i;

	i = 0;
	while (token_arr[i] != token)
		i++;
	ft_dprintf(2, "NAME_OF_EXE syntax error near unexpected token %s\n", str_arr[i]);
	return (FAILURE);
}

t_return_status is_a_meta(t_emt token)
{
	if (token > 8 && token != EOL)
		return (FAILURE);
	return (SUCCESS);
}
