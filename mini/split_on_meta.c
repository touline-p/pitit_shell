/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_on_meta.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <bpoumeau@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 17:27:20 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/02/26 18:40:52 by bpoumeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parsing.h"

t_token	*split_on_meta(t_token *tok)
{
	t_token *ret_val;

	ret_val = tok;
	while (tok->next)
	{
		get_next_emt(tok);
		tok = tok->next_word;
	}
	return (ret_val);
}

t_token	*get_next_emt(t_token *tok)
{
	t_emt	tmp;
	t_token *first;

	first = tok;
	tmp = tok->token;
	while (tok->next && tok->next->token == tmp)
		tok = tok->next;
	first->next_word = tok->next;
	tok->next = NULL;
	return (tok);
}