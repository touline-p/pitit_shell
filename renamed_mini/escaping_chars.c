/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escaping_chars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <bpoumeau@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 01:12:38 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/02/24 06:19:23 by bpoumeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parsing.h"

static t_ert	_escaping_chars_ep(void);

////TO DO cette fonction parcours toute la chaine pour tout les escape
//// Ce n'est pas le bon fonctionnement.
////SI TU CHANGE ESCAPING CHANGE AUSSI CE COMMENT

t_ert	escaping_chars(t_token *tok)
{
	t_token *pin;

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

t_ert	escape_process(t_token *last_pt, t_token *tok, t_token **voided)
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

static t_ert	_escaping_chars_ep(void)
{
	write(2, "syntax error near newline.\nLine can't be end by '\\'\n", 52);
	return (FAILURE);
}
