/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_articulation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 00:20:01 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/05/04 17:59:30 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parsing_incs/minishell_parsing.h"
#include "../../incs/parsing_incs/prototypes_parsing.h"
#include "../../incs/execution_incs/structures_execution.h"

#include "../../libft/libft.h"

t_return_status	get_lexed_str_token_lst_from_line(char *line, \
		t_string_token **str_tok_pt, char **env)
{
	t_token			*simple_tok_lst;
	t_string_token	*str_token_lst;

	(void)env;
	simple_tok_lst = token_lst_constructor(line);
	free(line);
	if (simple_tok_lst == NULL)
		return (FAILED_MALLOC);
	if (preserve_token_lst(simple_tok_lst) != SUCCESS)
		return (FAILURE);
	split_toklst_on_meta(simple_tok_lst);
	regroup_meta(simple_tok_lst);
	str_token_lst = token_lst_to_str_token(simple_tok_lst);
	if (str_token_lst == NULL)
		return (FAILED_MALLOC);
	*str_tok_pt = str_token_lst;
	return (SUCCESS);
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
