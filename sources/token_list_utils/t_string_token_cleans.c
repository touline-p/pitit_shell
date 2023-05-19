/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_string_tokens_cleans.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:28:32 by twang             #+#    #+#             */
/*   Updated: 2023/05/17 19:29:44 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	string_token_destructor(t_string_token *trash)
{
	t_string_token	*tmp;

	if (trash == NULL)
		return ;
	free(trash->content);
	tmp = trash->next;
	free(trash);
	string_token_destructor(tmp);
}

void	del_next_string_token(t_string_token *tok)
{
	t_string_token	*tmp;

	tmp = tok->next->next;
	free(tok->next->content);
	free(tok->next);
	tok->next = tmp;
}

void	del_space_token(t_string_token *tok)
{
	t_string_token	*pin;

	pin = tok;
	if (pin == NULL)
		return ;
	while (pin->next)
	{
		if (pin->next->token == E_SPACE || pin->next->token == TABULATION)
			del_next_string_token(pin);
		else
			pin = pin->next;
	}
}

void	del_empty_tokens(t_string_token *token_lst)
{
	while (token_lst->next->token != EOL)
	{
		if (token_lst->next->content == NULL
			|| *(char *)(token_lst->next->content) == 0)
			del_next_string_token(token_lst);
		else
			token_lst = token_lst->next;
	}
}

void	free_all_str(t_data *data)
{
	int	i;

	i = data->index;
	while (data->instructions_arr[i])
	{
		string_token_destructor(data->instructions_arr[i]);
		i++;
	}
}
