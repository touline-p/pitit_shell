/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_quoting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <bpoumeau@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 04:03:32 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/02/28 21:07:58 by bpoumeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"
#include "../../../incs/parsing_incs/minishell_parsing.h"

static t_return_status	_squoting_process_ep(void);

t_return_status	squoting_process(t_token *last_token, \
	t_token *token, t_token **end_of_quot_pt)
{
	(void)last_token;
	token->sign_char = - '\'';
	token = token->next;
	while (token->token != EOL && token->sign_char != '\'')
	{
		token->esec = SECURED;
		token = token->next;
	}
	if (token->token == EOL)
		return (_squoting_process_ep());
	*end_of_quot_pt = token;
	token->sign_char = - '\'';
	return (SUCCESS);
}

static t_return_status	_squoting_process_ep(void)
{
	write(2, \
	"syntax error near newline.\nLine can't end with : \'\n", \
	65);
	return (FAILURE);
}
