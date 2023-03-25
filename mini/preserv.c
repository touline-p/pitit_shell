/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preserv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <bpoumeau@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 03:57:05 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/03/10 02:08:26 by bpoumeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parsing.h"

#define DONO_INDX 3

static size_t	_code_from(char code);
t_ert			do_nothing(t_token *voided, t_token *also_voided, t_token **this_one_too);

t_ert	preserve_token_lst(t_token *token)
{
	t_token *pin;
	const t_preserv_act	act[] = {escape_process, squoting_process, dquoting_process, do_nothing};

	pin = token->next;
	while (token->token != EOL)
	{
		if (act[_code_from(pin->sign_char)](token, pin, &token) != SUCCESS)
			return (FAILURE);
		token = token->next;
		if (token)
			pin = token->next;
	}
	return (SUCCESS);
}

static size_t _code_from(char code)
{
	const char	*charset = "\\\'\"";
	char 		*tmp;

	tmp = ft_strchr(charset, code);
	if (tmp == NULL)
		return (DONO_INDX);
	return (tmp - charset);
}

t_ert	do_nothing(t_token *voided, t_token *also_voided, t_token **this_one_too)
{
	(void)voided;
	(void)also_voided;
	(void)this_one_too;
	return (SUCCESS);
}