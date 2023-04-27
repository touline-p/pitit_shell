/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangthea <wangthea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:57:21 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/04/06 17:35:50 by wangthea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"
#include "../../../incs/parsing_incs/minishell_parsing.h"

t_token	*token_constructor(t_emt emt, char msg)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->token = emt;
	new->sign_char = msg;
	new->next = NULL;
	new->esec = UNSECURED;
	new->next_word = NULL;
	return (new);
}

t_token	*token_constructor_esec(t_emt emt, char msg, t_esec esec)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->token = emt;
	new->sign_char = msg;
	new->next = NULL;
	new->esec = esec;
	new->next_word = NULL;
	return (new);
}

void	token_lst_clear(t_token *trash)
{
	t_token	*tmp;

	while (trash)
	{
		tmp = trash->next;
		del_token(trash);
		trash = tmp;
	}
}

void	del_next_token(t_token *token)
{
	t_token	*tmp;

	tmp = token->next->next;
	del_token(token->next);
	token->next = tmp;
}

void	del_first_token(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	*token = tmp->next;
	del_token(tmp);
}
