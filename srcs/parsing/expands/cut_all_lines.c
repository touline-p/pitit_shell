/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_all_lines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 18:54:31 by twang             #+#    #+#             */
/*   Updated: 2023/05/16 18:56:54 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/execution_incs/minishell_execution.h"
#include "../../../incs/parsing_incs/minishell_parsing.h"

t_return_status	cut_all_lines(t_string_token *string_token_lst)
{
	while (string_token_lst->token != EOL)
	{
		if (string_token_lst->token == STRING
			&& cut_line_on(string_token_lst->content, \
			&(string_token_lst->str_arr)))
			return (FAILED_MALLOC);
		string_token_lst = string_token_lst->next;
	}
	return (SUCCESS);
}

t_return_status	join_all_lines(t_string_token *string_token_lst, char **env)
{
	while (string_token_lst->token != EOL)
	{
		if (string_token_lst->token == STRING
			&& join_arr_on(string_token_lst->str_arr, \
			&(string_token_lst->content), env) != SUCCESS)
			return (FAILED_MALLOC);
		string_token_lst->str_arr = NULL;
		string_token_lst = string_token_lst->next;
	}
	return (SUCCESS);
}

t_return_status	expand_line(char **line_pt, char **env)
{
	char	**tmp_arr;

	if (SUCCESS != cut_line_on(*line_pt, &tmp_arr)
		|| SUCCESS != join_arr_on(tmp_arr, line_pt, env))
		return (FAILURE);
	return (SUCCESS);
}
