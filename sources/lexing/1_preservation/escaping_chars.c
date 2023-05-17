/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escaping_chars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 01:12:38 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/05/17 19:37:16 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*---- prototypes ------------------------------------------------------------*/

static t_return_status	_escaping_chars_ep(void);

/*----------------------------------------------------------------------------*/

t_return_status	escaping_chars(t_token *tok)
{
	t_token	*pin;

	pin = tok->next;
	while (pin->token != EOL)
	{
		if (escape_process(tok, pin, &tok) != SUCCESS)
			return (_escaping_chars_ep());
		tok = tok->next;
		pin = tok->next;
	}
	return (SUCCESS);
}

t_return_status	escape_process(t_token *last_pt, t_token *tok, t_token **voided)
{
	(void)voided;
	if (tok->token != LETTER
		|| tok->sign_char != '\\'
		|| tok->esec != UNSECURED)
		return (SUCCESS);
	if (tok->next->token == EOL)
		return (FAILURE);
	tok->next->esec = SECURED;
	del_next_token(last_pt);
	return (SUCCESS);
}

static t_return_status	_escaping_chars_ep(void)
{
	write(2, "syntax error near newline.\nLine can't be end by '\\'\n", 52);
	return (FAILURE);
}
