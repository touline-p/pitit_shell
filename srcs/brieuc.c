/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brieuc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:53:30 by wangthea          #+#    #+#             */
/*   Updated: 2023/03/24 18:00:37 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

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

t_string_token *token_lst_to_str_token(t_token *tok)
{
	t_string_token	*str_token_list;
	t_string_token	*mem;
	t_token 		*pin;

	mem = NULL;
	if (string_token_creator_on(&str_token_list) != SUCCESS)
		return (_token_lst_to_str_token_ep(tok, mem));
	str_token_list->token = START;
	mem = str_token_list;
	pin = tok->next;
	while (pin->token != EOL)
	{
		if (_get_str_token_on_and_reset_pin(&str_token_list->next, &pin) != SUCCESS)
			return (_token_lst_to_str_token_ep(tok, mem));
		str_token_list = str_token_list->next;
	}
	if (string_token_creator_on(&str_token_list->next) != SUCCESS)
		return (_token_lst_to_str_token_ep(tok, mem));
	str_token_list->next->token = EOL;
	token_lst_clear(tok);
	return (mem);
}

