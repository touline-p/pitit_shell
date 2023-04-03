//
// Created by bpoumeau on 4/3/23.
//

#include "../../../incs/execution_incs/minishell_execution.h"
#include "../../../incs/parsing_incs/minishell_parsing.h"

t_return_status cut_all_lines(t_string_token *string_token_lst)
{
	while (string_token_lst->token != EOL)
	{
		if (string_token_lst->token == STRING
			&& cut_line_on(string_token_lst->content, &(string_token_lst->str_arr)))
			return (FAILED_MALLOC);
		string_token_lst = string_token_lst->next;
	}
	return (SUCCESS);
}

t_return_status join_all_lines(t_string_token *string_token_lst, char **env)
{
	while (string_token_lst->token != EOL)
	{
		if (string_token_lst->token == STRING
			&& join_arr_on(string_token_lst->str_arr, &(string_token_lst->content), env) != SUCCESS)
			return (FAILED_MALLOC);
		string_token_lst->str_arr = NULL;
		string_token_lst = string_token_lst->next;
	}
	return (SUCCESS);
}