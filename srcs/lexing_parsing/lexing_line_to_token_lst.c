//
// Created by bpoumeau on 3/15/23.
//

#include "basic_enums_struct.h"
#include "stdlib.h"

#include "mini_parsing.h"
t_str_token_lst	*lexing_line_to_token_lst(char *line)
{
	t_str_token_lst	*token_lst;
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