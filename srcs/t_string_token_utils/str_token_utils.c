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

#include "mini_parsing.h"

int	next_control_operator_is_a_pipe(t_string_token *tok)
{
	while (tok->token != EOL && tok->token != AMPERSAND && tok->token != AND && tok->token != OR)
	{
		if (tok->token == PIPE)
			return (1);
		tok = tok->next;
	}
	return (0);
}
