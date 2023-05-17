/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 23:58:51 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/05/17 19:47:43 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	t_token	*pin;
	t_token	*new;

	new = NULL;
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

t_return_status	insert_str_in_tkn_lst(t_token *token_lst, char *str, \
										t_esec insert_esec)
{
	t_token	*next;
	t_token	*new;

	next = token_lst->next;
	new = token_lst_constructor_word(str, insert_esec);
	if (!new)
		return (FAILED_MALLOC);
	token_lst->next = new;
	while (token_lst->next != NULL)
	{
		token_lst = token_lst->next;
		token_lst->esec = insert_esec;
	}
	token_lst->next = next;
	return (SUCCESS);
}

int	len_to_next_type(t_token *pin)
{
	int	i;

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
