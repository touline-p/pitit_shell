//
// Created by bpoumeau on 3/15/23.
//

#include "minishell_parsing.h"
#include "structures_execution.h"

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
