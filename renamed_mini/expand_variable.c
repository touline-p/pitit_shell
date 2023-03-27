/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <bpoumeau@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 21:21:54 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/03/09 14:44:17 by bpoumeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parsing.h"

t_ert		_substitute_for_env_variable(t_token **token, char **env);
char		*_get_env_variable(t_token *token, char **env);
static char *_check_for_env_variable(t_token *tok, char *env);

t_ert	expand_dollars(t_token *token_lst, char **env)
{
	t_token	*pin;

	pin = token_lst->next;
	while (pin->token != EOL)
	{
		if (pin->next->sign_char == '$'
			&& pin->next->esec == UNSECURED
			&& _substitute_for_env_variable(&pin, env) != SUCCESS)
			return (MLC_ERR);
		pin = pin->next;
	}
	return (SUCCESS);
}

t_ert	_substitute_for_env_variable(t_token **last_token, char **env)
{
	char *variable_string;

	variable_string = _get_env_variable((*last_token)->next, env);
	del_next_token(*last_token);
	del_next_word(*last_token);
	if (variable_string != NULL &&
		insert_str_in_tkn_lst(*last_token, variable_string, UNSECURED) != SUCCESS)
		return (MLC_ERR);
	return (SUCCESS);
}

char *_get_env_variable(t_token *token, char **env)
{
	char *variable_str;

	variable_str = NULL;
	while (variable_str == NULL && *env)
	{

		variable_str = _check_for_env_variable(token->next, *env);
		env++;
	}
	return (variable_str);
}

static char 	*_check_for_env_variable(t_token *tok, char *env_str)
{
	(void)tok;
	(void)env_str;
	while (ft_isalnum(tok->sign_char) && *env_str == tok->sign_char)
	{
		env_str++;
		tok = tok->next;
	}
	if (*env_str == '=')
		return (++env_str);
	return (NULL);
}
