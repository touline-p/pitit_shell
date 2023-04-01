/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_string_token_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:25:09 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/03/27 14:28:55 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/execution_incs/minishell_execution.h"
#include "../../incs/parsing_incs/minishell_parsing.h"
#include "minishell_parsing.h"

t_string_token	*string_token_creator(void)
{
	t_string_token	*new;

	new = malloc(sizeof(t_string_token));
	if (new == NULL)
		return (NULL);
	new->next = NULL;
	new->content = NULL;
	new->token = NONE;
	return (new);
}

t_return_status	string_token_creator_on(t_string_token **tok_pt)
{
	t_string_token *new;

	new = string_token_creator();
	if (new == NULL)
		return (FAILED_MALLOC);
	*tok_pt = new;
	return (SUCCESS);
}

void	string_token_destructor(t_string_token *trash)
{
	t_string_token *tmp;

	if (trash == NULL)
		return ;
	free(trash->content);
	tmp = trash->next;
	free(trash);
	string_token_destructor(tmp);
}

void	cpy_token_lst_to_str(t_token *tok, char *str)
{
	int i;

	i = 0;
	str[0] = tok->sign_char;
	while (tok->token == LETTER)
	{
		if (!is_from(tok->sign_char, "\'\"") || tok->esec == SECURED)
		{
			str[i] = tok->sign_char;
			i++;
		}
		tok = tok->next;
	}
	str[i] = 0;
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
	t_string_token *pin;

	pin = tok;
	while (pin->next->token != EOL)
	{
		if (pin->next->token == E_SPACE || pin->next->token == TABULATION)
			del_next_string_token(pin);
		else
			pin = pin->next;
	}
}

t_return_status string_token_new_on(void *content, t_emt emt, t_string_token **str_token_pt)
{
	t_string_token *new;

	new = malloc(sizeof(t_string_token *));
	if (!new)
		return (FAILED_MALLOC);
	new->content = content;
	new->token = emt;
	*str_token_pt = new;
	return (SUCCESS);
}

t_return_status str_arr_to_str_token_lst(char **split, t_string_token **str_token_pt)
{
	t_string_token	*new_lst;
	char 			**split_tmp;

	split_tmp = split;
	if (string_token_new_on(*(split++), STRING, &new_lst) != SUCCESS)
		return (FAILED_MALLOC);
	free((*str_token_pt)->content);
	free(*str_token_pt);
	*str_token_pt = new_lst;
	while (new_lst->content != NULL)
	{
		if (string_token_new_on(*(split++), STRING, &(new_lst->next)) != SUCCESS)
		new_lst = new_lst->next;
	}
	free(split_tmp);
	return (SUCCESS);
}

void del_empty_tokens(t_string_token *token_lst)
{
	while (token_lst->next->token != EOL)
	{
		if (token_lst->next->content == NULL || *(char *)(token_lst->next->content) == 0)
			del_next_string_token(token_lst);
		else
			token_lst = token_lst->next;
	}
}

t_return_status	split_t_string_token_on_space(t_string_token **token)
{
	char			**split;
	t_string_token	*token_lst;

	split = ft_split((*token)->content, ' ');
	free((*token)->content);
	free(*token);
	if (split == NULL)
		return (FAILED_MALLOC);
	if (str_arr_to_str_token_lst(split, &token_lst) != SUCCESS)
		return (FAILED_MALLOC);
	*token = token_lst;
	return (SUCCESS);
}