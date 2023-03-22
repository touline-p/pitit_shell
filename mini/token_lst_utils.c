/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <bpoumeau@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:57:21 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/03/10 03:57:39 by bpoumeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parsing.h"

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

t_token *token_constructor_esec(t_emt emt, char msg, t_esec esec)
{
	t_token *new;

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
	t_token *tmp;

	while (trash)
	{
		tmp = trash->next;
		del_token(trash);
		trash = tmp;
	}
}

void	del_next_token(t_token *token)
{
	t_token *tmp;

	tmp = token->next->next;
	del_token(token->next);
	token->next = tmp;
}

void	del_first_token(t_token **token)
{
	t_token *tmp;

	tmp = *token;
	*token = tmp->next;
	del_token(tmp);
}

void	del_next_word(t_token *token)
{
	while (ft_isalnum(token->next->sign_char))
	{
		del_next_token(token);
	}
}

void	del_token(t_token *token)
{
	token_lst_clear(token->next_word);
	free(token);
}

t_token	*token_lst_constructor_word(char *string, t_esec esec)
{
	t_token *pin;
	t_token *new;

	if (*string != '\0')
		new = token_constructor_esec(LETTER, *(string++), esec);
	if (!new)
		return (NULL);
	pin = new;
	while (*string != '\0')
	{
		pin->next = token_constructor_esec(LETTER, *(string++), esec);
		if (!pin->next)
		{
			token_lst_clear(new);
			return (NULL);
		}
		pin = pin->next;
	}
	return (new);
}

t_ert	insert_str_in_tkn_lst(t_token *token_lst, char *str, t_esec insert_esec)
{
	t_token *next;
	t_token *new;

	next = token_lst->next;
	new = token_lst_constructor_word(str, insert_esec);
	if (!new)
		return (MLC_ERR);
	token_lst->next = new;
	while (token_lst->next != NULL)
	{
		token_lst = token_lst->next;
		token_lst->esec = insert_esec;
	}
	token_lst->next = next;
	return (SUCCESS);
}

int		len_to_next_type(t_token *pin)
{
	int i;

	if (pin->token == LETTER)
	{
		i = 0;
		while (pin->token == LETTER)
		{
			pin = pin->next;
			i++;
		}
		return (i);
	}
	else
		return (1);
}
