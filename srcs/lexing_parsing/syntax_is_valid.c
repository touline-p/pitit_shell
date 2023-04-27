/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_line_to_token_lst.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 00:19:36 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/04/27 00:19:38 by bpoumeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"
#include "../../incs/execution_incs/structures_execution.h"
#include "../../incs/parsing_incs/minishell_parsing.h"

static t_return_status	_syntax_is_valid_ep(t_emt token);
bool					is_a_meta(t_emt token);
bool					is_a_redir(t_emt token);

t_return_status	syntax_is_valid(t_string_token *lst_to_check)
{
	t_string_token	*pin;

	pin = lst_to_check;
	if (lst_to_check->next->token == EOL)
		return (FAILURE);
	if (is_a_meta(pin->next->token) == true
		&& is_a_redir(pin->next->token) == false)
		return (_syntax_is_valid_ep(pin->next->token));
	pin = pin->next;
	while (pin->token != EOL)
	{
		if (is_a_meta(pin->token) == true
			&& is_a_meta(pin->next->token) == true)
			return (_syntax_is_valid_ep(pin->next->token));
		pin = pin->next;
	}
	return (SUCCESS);
}

static t_return_status	_syntax_is_valid_ep(t_emt token)
{
	const char	str_arr[9][20] = {"'|'", "'||'", "'&&'", \
	"'&'", "'>'", "'<'", "'>>'", "'<<'", "'newline'"};
	const t_emt	token_arr[] = {PIPE, OR, AND, \
	AMPERSAND, CHEVRON_OT, CHEVRON_IN, APPENDS, HERE_DOC, EOL};
	size_t		i;

	i = 0;
	while (token_arr[i] != token)
		i++;
	dprintf(2,
		"%s : syntax error near unexpected token %s\n",
		NAME_OF_EXE,
		str_arr[i]);
	return (FAILURE);
}

bool	is_a_meta(t_emt token)
{
	if (token > 8 && token != EOL)
		return (false);
	return (true);
}

bool	is_a_redir(t_emt token)
{
	if (token == CHEVRON_OT || token == CHEVRON_IN || token == HERE_DOC)
		return (true);
	return (false);
}