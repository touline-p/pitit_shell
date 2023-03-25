/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quoting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <bpoumeau@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 04:52:43 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/03/09 14:34:07 by bpoumeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parsing.h"

static t_ert	_dquoting_process_ep(void);

t_ert	dquoting_process(t_token *last_token, t_token *token, t_token **end_of_quot_pt)
{
	t_token	*pin;

	pin = token->next;
	while ((pin->token != EOL && pin->sign_char != '\"') || pin->esec == SECURED)
	{
		if (pin->sign_char == '\\' && is_from(pin->next->sign_char, "\\\"$"))
			escape_process(last_token, pin, &last_token);
		else if (pin->sign_char != '$')
			pin->esec = SECURED;
		last_token = last_token->next;
		pin = last_token->next;
	}
	if (pin->token == EOL)
		return (_dquoting_process_ep());
	*end_of_quot_pt = pin;
	return (SUCCESS);
}

static t_ert	_dquoting_process_ep(void)
{
	write(2, "syntax error near newline.\nLine can't end with open double quote\n", 65);
	return (FAILURE);
}
