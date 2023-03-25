/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <bpoumeau@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 14:11:04 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/03/10 02:04:09 by bpoumeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parsing.h"

static t_token	*_token_lst_constructor_ep(t_token *trash, t_token *ret_val);

t_token	*token_lst_constructor(char *str)
{
	t_token	*token;
	t_token	*pin;

	token = token_constructor(START, STRT_CHR);
	pin = token;
	while (*str != EOSTR)
	{
		pin->next = token_constructor(LETTER, *str);
		if (!pin->next)
			return (_token_lst_constructor_ep(token, NULL));
		pin = pin->next;
		str++;
	}
	pin->next = token_constructor(EOL, EOSTR);
	return (token);
}

static t_token	*_token_lst_constructor_ep(t_token *trash, t_token *ret_val)
{
	token_lst_clear(trash);
	return (ret_val);
}