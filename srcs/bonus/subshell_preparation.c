//
// Created by bpoumeau on 5/12/23.
//

#include "../../incs/execution_incs/minishell_execution.h"
#include "../../incs/parsing_incs/minishell_parsing.h"

char	**subshell_preparation(t_string_token **start)
{
	t_string_token	*ret_val;
	t_string_token	*pin;

	ret_val = (*start)->next;
	go_to_next_(C_PRTSS, ret_val->next, &pin);
	ret_val->token = START;
	pin->token = EOL;
	(*start)->next = pin->next;
	pin->next = NULL;
	*start = (*start)->next;
	return ((char **)ret_val);
}