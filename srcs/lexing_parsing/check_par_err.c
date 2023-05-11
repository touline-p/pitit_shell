//
// Created by bpoumeau on 5/10/23.
//

#include "../../incs/execution_incs/minishell_execution.h"
#include "../../incs/parsing_incs/minishell_parsing.h"

static bool	_check_for_par(t_string_token *str_tok_lst)
{
	while (str_tok_lst->token != EOL && str_tok_lst->token != AND && str_tok_lst->token != OR && str_tok_lst->token != C_PRTSS)
	{
		if (str_tok_lst->token == O_PRTSS)
			return (true);
		str_tok_lst = str_tok_lst->next;
	}
	return (false);
}

static bool	_check_for_solo_string_till(t_emt till, t_string_token *str_tok_lst)
{
	while (str_tok_lst->token != till && str_tok_lst->token != EOL && str_tok_lst->token != AND && str_tok_lst->token != OR)
	{
		if (str_tok_lst->token == STRING)
			return (true);
		str_tok_lst = str_tok_lst->next;
	}
	return (false);
}

static bool	_par_process(t_string_token *str_tok_lst)
{
	t_string_token	*tmp;

	if (str_tok_lst->token != O_PRTSS)
		go_to_next_(O_PRTSS, str_tok_lst, &tmp);
	else
		tmp = str_tok_lst;
	if (_check_for_solo_string_till(O_PRTSS, str_tok_lst) == true)
	{
		tmp->token = SYN_ERR;
		return (true);
	}
	go_to_next_(C_PRTSS, tmp->next, &str_tok_lst);
	if (_check_for_par(tmp->next))
		if (_par_process(tmp->next))
			return (true);
	if (_check_for_solo_string_till(C_PRTSS, str_tok_lst->next) == true
		|| _check_for_par(str_tok_lst))
		str_tok_lst->token = SYN_ERR;
	return (false);
}

void check_par_err(t_string_token *str_tok_lst)
{
	if (_check_for_par(str_tok_lst->next))
	{
		if (_par_process(str_tok_lst) == true)
			return;
	}
	go_to_next_logical_door(str_tok_lst->next, &str_tok_lst);
	if (str_tok_lst->token != EOL)
		check_par_err(str_tok_lst);
}