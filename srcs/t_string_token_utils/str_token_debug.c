/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_token_debug.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangthea <wangthea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 01:06:10 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/04/06 21:02:21 by wangthea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/execution_incs/minishell_execution.h"
#include "../../incs/parsing_incs/minishell_parsing.h"

void	display_t_emt_string(t_string_token *token);

void	display_str_token(t_string_token *tok)
{
	while (tok)
	{
		if (tok->token == STRING)
		{
			printf("<%s>", tok->content);
		}
		else
			display_t_emt_string(tok);
		tok = tok->next;
	}
	printf("\n");
}

void	display_t_emt_string(t_string_token *token)
{
	const char	*msgarr[] = {"start", "_pipe_", "ifnot", "fd_in", "fd_ot", "__or__", "_and_", "hrdoc", "appnd", "lfpar", "rtpar", "smcln", "space", "_tab_", "_ltr_","end_l", "_str_", "dolrs"};
	char		*msg;

	if (token == NULL)
		return ;
	if (token->token == STRING) {
		msg = ft_strdup(token->content);
	}
	else
		msg = ft_strdup((char *)msgarr[token->token]);
	printf("<%.5s>", msg);
	free(msg);
}
