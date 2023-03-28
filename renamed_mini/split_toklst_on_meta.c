/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_meta.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <bpoumeau@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 01:07:01 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/03/09 19:26:36 by bpoumeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parsing.h"
#include "./libft/libft.h"

static	void	_get_signal_from_char(char sign_char, t_emt *emt_pt);
static void		_regroup_ft(t_token *tok);

t_token *split_toklst_on_meta(t_token *tok)
{
	t_token *tmp;

	tmp = tok;
	while (tok && tok->token != EOL)
	{
		if (tok->esec == UNSECURED)
			_get_signal_from_char(tok->sign_char, &(tok->token));
		tok = tok->next;
	}
	return (tmp);
}

static	void	_get_signal_from_char(char sign_char, t_emt *emt_pt)
{
	const t_emt	emt_arr[] = {PIPE, AMPERSAND, CHEVRON_IN, CHEVRON_OT, \
						O_PRTSS, C_PRTSS, SEMICOLON, SPACE};
	const char 	*metachar_set = METACHAR_SET;
	char		*signal;

	signal = ft_strchr(metachar_set, sign_char);
	if (signal)
		*emt_pt = emt_arr[signal - metachar_set];
}

t_token *regroup_meta(t_token *tok)
{
	t_token *ret;

	ret = tok;
	while (tok->next && tok->next->token != EOL)
	{
		if (tok->token != LETTER && tok->token == tok->next->token)
			_regroup_ft(tok);
		tok = tok->next;
	}
	return (ret);
}

static void	_regroup_ft(t_token *tok)
{
	t_token *tmp;

	if (tok->token >= OR)
		return ;
	tok->token += 4;
	tmp = tok->next->next;
	del_token(tok->next);
	tok->next = tmp;
}
