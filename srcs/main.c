/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:53:30 by wangthea          #+#    #+#             */
/*   Updated: 2023/03/24 17:50:16 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

#include "fcntl.h"
#include <unistd.h>

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

t_ert	string_token_creator_on(t_string_token **tok_pt)
{
	t_string_token *new;

	new = string_token_creator();
	if (new == NULL)
		return (MLC_ERR);
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
		if (pin->next->token == SPACE || pin->next->token == TABULATION)
			del_next_string_token(pin);
		else
			pin = pin->next;
	}
}

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
	const char	*msgarr[] = {"start", "pipe", "and", "fd_in", "fd_out", "or", "ifnot", "heredoc", "append", "lfpar", "rtpar", "smcln", "space", "_tab_", "_ltr_","end_l", "_str_", "dolrs"};
	char		*msg;

	if (token == NULL)
		return ;
	if (token->token == STRING) {
		msg = ft_strdup(token->content);
	}
	else
		msg = ft_strdup((char *)msgarr[token->token]);
	printf("<%s>", msg);
	free(msg);
}

t_string_token	*parsing_constructor(char *str, char **env)
{
	t_token			*tok;
	t_string_token	*str_tok;

	tok = token_lst_constructor(str);
	preserve_token_lst(tok);
	expand_dollars(tok, env);
	split_toklst_on_meta(tok);
	regroup_meta(tok);
	str_tok = token_lst_to_str_token(tok);
	del_space_token(str_tok);
	display_str_token(str_tok);
	return (str_tok);
}

int	main(int ac, char **av, char **env)
{	
	ft_printf(PURPLE"Bonjour genies Bpoumeau et Twang\n"END);
	
	// char			*line;
	// t_str_token_lst	*token_lst;
	
	// while (MINI_SHELL_MUST_GO_ON)
	// {
	// 	rl_signal_reset();
	// 	line = readline(PURPLE"prompt : >"END);
	// 	token_lst = lexing_line_to_token_lst(line, env);
	// 	execute_token_lst(token_lst);
	// }

	t_string_token	*str_tok = parsing_constructor(av[1], env);
	display_str_token(str_tok);
	
	return (0);
}
