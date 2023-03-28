/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suppress_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <bpoumeau@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:54:44 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/03/09 19:15:30 by bpoumeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parsing.h"

void	suppress_quotes(t_token *tok)
{
	t_token *pin;

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