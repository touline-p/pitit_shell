/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_string_token_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:25:09 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/05/17 19:31:16 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cpy_token_lst_to_str(t_token *tok, char *str)
{
	int	i;

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

t_return_status	string_token_new_on(void *content, t_emt emt, \
									t_string_token **str_token_pt)
{
	t_string_token	*new;

	new = malloc(sizeof(t_string_token));
	if (!new)
		return (FAILED_MALLOC);
	new->content = content;
	new->token = emt;
	new->next = NULL;
	*str_token_pt = new;
	return (SUCCESS);
}

t_return_status	str_arr_to_str_token_lst(char **split, \
										t_string_token **str_token_pt)
{
	t_string_token	*new_lst;
	char			**split_tmp;

	split_tmp = split;
	new_lst = NULL;
	if (*split && string_token_new_on(*(split++), STRING, \
		&new_lst) != SUCCESS)
		return (FAILED_MALLOC);
	free(*str_token_pt);
	*str_token_pt = new_lst;
	while (*split)
	{
		if (string_token_new_on(*(split++), STRING, \
			&(new_lst->next)) != SUCCESS)
			new_lst = new_lst->next;
	}
	free(split_tmp);
	return (SUCCESS);
}

t_return_status	split_t_string_token_on_space(t_string_token **token)
{
	char			**split;
	t_string_token	*token_lst;

	token_lst = NULL;
	split = ft_split((*token)->content, ' ');
	ft_print_split(split);
	if (split == NULL)
		return (FAILED_MALLOC);
	printf("je suis lla\n");
	if (str_arr_to_str_token_lst(split, &token_lst) != SUCCESS)
		return (FAILED_MALLOC);
	display_str_token(token_lst);
	*token = token_lst;
	return (SUCCESS);
}
