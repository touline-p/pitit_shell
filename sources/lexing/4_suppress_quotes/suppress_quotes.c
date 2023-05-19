/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suppress_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:54:44 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/05/17 19:44:55 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	suppress_quotes(t_token *tok)
{
	t_token	*pin;

	pin = tok;
	while (pin->next->token != EOL)
	{
		if (pin->next->esec == UNSECURED \
		&& is_from(pin->next->sign_char, "\'\""))
			del_next_token(pin);
		else
			pin = pin->next;
	}
}
