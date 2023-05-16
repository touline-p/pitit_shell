/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_quoting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 04:03:32 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/05/16 14:23:57 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"
#include "../../../incs/parsing_incs/minishell_parsing.h"

static t_return_status	_squoting_process_ep(void);

t_return_status	squoting_process(t_token *last_token, \
	t_token *token, t_token **end_of_quot_pt)
{
	(void)last_token;
	token->sign_char = - '\'';
	token = token->next;
	while (token->token != EOL && token->sign_char != '\'')
	{
		token->esec = SECURED;
		token = token->next;
	}
	if (token->token == EOL)
		return (_squoting_process_ep());
	*end_of_quot_pt = token;
	token->sign_char = - '\'';
	return (SUCCESS);
}

static t_return_status	_squoting_process_ep(void)
{
	char	*str;

	str = "syntax error near newline.\nLine can't end with open : \'\n";
	write(2, str, 57);
	g_ret_val = 2;
	return (FAILURE);
}
