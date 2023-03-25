/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <bpoumeau@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:58:54 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/03/09 13:43:05 by bpoumeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by bpoumeau on 2/21/23.
//

# include "test_mini.h"
# include "basic_enums.h"
# include "mini_parsing.h"


void	display_tokens(t_token *token_lst)
{
	t_token *next_block;

	while (token_lst)
	{
		next_block = token_lst->next_word;
		while (token_lst != NULL)
		{
			display_t_emt(token_lst);
			token_lst = token_lst->next;
		}
		printf("\n");
		token_lst = next_block;
	}
	printf("\n");
}

void	display_t_emt(t_token *token)
{
	const char	*msgarr[] = {"start", "pipe_", "_and_", "fd_in", "fd_ot", "_or__", "ifnot", "hrdoc", "appnd", "lfpar", "rtpar", "smcln", "space", "_tab_", "_ltr_","end_l", "_str_", "dolrs"};
	char		*msg;

	if (token->token == LETTER) {
		msg = ft_strdup("     ");
		if (token->esec == SECURED)
		{
			msg[0] = '_';
			msg[1] = '_';
			msg[3] = '_';
			msg[4] = '_';
		}
		msg[2] = token->sign_char;
	}
	else
		msg = ft_strdup((char *)msgarr[token->token]);
	printf("<%.5s>", msg);
	free(msg);
}

void	put_esec(t_token *tok)
{
	if (tok->esec == SECURED)
		printf("-> secured");
	else
		printf("-> unsecured");
}
