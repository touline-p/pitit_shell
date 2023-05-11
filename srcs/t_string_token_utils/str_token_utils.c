/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_token_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <bpoumeau@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:43:42 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/03/11 16:53:24 by bpoumeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/execution_incs/minishell_execution.h"
#include "../../incs/parsing_incs/minishell_parsing.h"
#include "minishell_parsing.h"

int	next_control_operator_is_a_pipe(t_string_token *tok)
{
	while (tok->token != EOL && tok->token != AMPERSAND \
		&& tok->token != AND && tok->token != OR)
	{
		if (tok->token == PIPE)
			return (1);
		tok = tok->next;
	}
	return (0);
}

char *format_string_token(t_string_token *token)
{
	const char	*msgarr[] = {"start", "\'|", "ifnot", "\'<", \
	"\'>", "\'||", "\'&&", "\'<<", "\'>>", "lfpar", \
	"\')", "\';", "\' ", "\'\t", "_ltr_", "\'newline", \
	"_str_\n", "dolrs\n", "file_\n", "hr_dt\n", "\'syner"};

	if (token->token == STRING)
		return (ft_strjoin(token->content, "'\n"));
	return (ft_strjoin(msgarr[token->token], "'\n"));
}
