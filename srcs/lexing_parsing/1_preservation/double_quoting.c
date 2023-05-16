/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quoting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 04:52:43 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/05/16 10:59:32 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/parsing_incs/minishell_parsing.h"

static t_return_status	_dquoting_process_ep(void);

t_return_status	dquoting_process(t_token *last_token, \
	t_token *token, t_token **end_of_quot_pt)
{
	t_token	*pin;

	pin = token->next;
	token->sign_char = - '\"';
	while ((pin->token != EOL && pin->sign_char != '\"')
		|| pin->esec == SECURED)
	{
		if (pin->sign_char != '$')
			pin->esec = SECURED;
		last_token = last_token->next;
		pin = last_token->next;
	}
	if (pin->token == EOL)
		return (_dquoting_process_ep());
	pin->sign_char = - '\"';
	*end_of_quot_pt = pin;
	return (SUCCESS);
}

static t_return_status	_dquoting_process_ep(void)
{
	char	*str;

	str = "syntax error near newline.\nLine can't end with open : \"\n";
	write(2, str, 57);
	return (FAILURE);
}
