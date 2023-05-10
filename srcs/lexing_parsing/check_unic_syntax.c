//
// Created by bpoumeau on 5/10/23.
//

#include "../../incs/execution_incs/minishell_execution.h"
#include "../../incs/parsing_incs/minishell_parsing.h"

typedef bool (*t_act_update)(t_string_token ** token);

bool update_to_filename(t_string_token **tmp)
{
	if ((*tmp)->next->token != STRING)
	{
		(*tmp)->token = SYN_ERR;
		return (false);
	}
	(*tmp)->next->token = FILE_NAME;
	(*tmp) = (*tmp)->next;
	return (true);
}

bool	update_to_hr_data(t_string_token **tmp)
{
	if ((*tmp)->next->token != STRING)
	{
		(*tmp)->token = SYN_ERR;
		return (false);
	}
	(*tmp)->next->token = HR_DATA;
	(*tmp) = (*tmp)->next;
	return (true);
}

bool	do_nothing_ut(t_string_token **tmp)
{
	display_str_token(*tmp);
	*tmp = (*tmp)->next;
	return (true);
}

void update_tokens(t_string_token *str_tok_lst)
{
	const	t_act_update	ft_arr[] = {&do_nothing_ut, &do_nothing_ut, &do_nothing_ut, &update_to_filename, &update_to_filename,  &do_nothing_ut, &do_nothing_ut, &update_to_hr_data, &update_to_filename, &do_nothing_ut, &do_nothing_ut};
	t_string_token	*tmp;

	tmp = str_tok_lst;
	while (tmp->token != EOL)
		if (!ft_arr[str_tok_lst->token](&str_tok_lst))
			break ;
	display_str_token(str_tok_lst);
}
