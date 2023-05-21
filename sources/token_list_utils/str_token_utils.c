/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_token_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangthea <wangthea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:43:42 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/05/18 19:21:29 by wangthea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*format_string_token(t_string_token *token)
{
	const char	*msgarr[] = {"start", "\'|", "ifnot", "\'<", \
	"\'>", "\'||", "\'&&", "\'<<", "\'>>", "lfpar", \
	"\')", "\';", "\' ", "\'\t", "_ltr_", "\'newline", \
	"_str_\n", "dolrs\n", "file_\n", "hr_dt\n", "\'syner"};

	if (token->token == STRING)
		return (ft_strjoin(token->content, "'\n"));
	return (ft_strjoin(msgarr[token->token], "'\n"));
}
