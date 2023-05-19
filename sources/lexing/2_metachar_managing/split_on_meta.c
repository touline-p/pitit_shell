/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_on_meta.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 17:27:20 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/05/17 19:40:54 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*split_on_meta(t_token *tok)
{
	t_token	*ret_val;

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
	t_token	*first;

	first = tok;
	tmp = tok->token;
	while (tok->next && tok->next->token == tmp)
		tok = tok->next;
	first->next_word = tok->next;
	tok->next = NULL;
	return (tok);
}
