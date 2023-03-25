/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_block_building_utils.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <bpoumeau@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:02:15 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/03/12 00:05:59 by bpoumeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by bpoumeau on 3/11/23.
//

#include "mini_parsing.h"

t_ert	dn(t_instruction_block_tree *block, t_string_token *to, char **env);
t_ert	open_chevron_in(t_instruction_block_tree *block, t_string_token *tok, char **env);
t_ert	open_chevron_out(t_instruction_block_tree *block, t_string_token *tok, char **env);
t_ert	open_append_in(t_instruction_block_tree *block, t_string_token *tok, char **env);
t_ert	get_here_doc_fd(t_instruction_block_tree *block, t_string_token *tok, char **env);

t_ert	stock_last_redirect(t_instruction_block_tree *block, t_string_token *tok, char **env)
{
	const t_fd_ft	fd_ft_arr[] = {&dn, &dn, &dn, &open_chevron_in, &open_chevron_out, &dn, &dn, &dn, \
		&open_append_in, &get_here_doc_fd, &dn, &dn, &dn, &dn, &dn, &dn, &dn, &dn, &dn, &dn, &dn, &dn};
	t_ert			ret_val;

	ret_val = SUCCESS;
	while (tok->token != EOL && is_control_operator(tok->token) != SUCCESS)
	{
		if (fd_ft_arr[tok->token](block, tok, env) != SUCCESS)
			ret_val = FAILURE;
		tok = tok->next;
	}
	return (ret_val);
}

t_ert	dn(t_instruction_block_tree *block, t_string_token *tok, char **env)
{
	(void)block;
	(void)tok;
	(void)env;
	return (SUCCESS);
}

t_ert	open_chevron_in(t_instruction_block_tree *block, t_string_token *tok, char **env)
{
	int fd;

	(void)env;
	fd = open(tok->next->content, O_RDONLY | O_CREAT, 0644);
	if (fd == -1)
		per_n_set_errno((char *)tok->next->content);
	if (block->fd_in > 2)
		close(block->fd_in);
	block->fd_in = fd;
	return (SUCCESS);
}

t_ert	open_chevron_out(t_instruction_block_tree *block, t_string_token *tok, char **env)
{
	int	fd;

	(void)env;
	fd = open(tok->next->content, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		per_n_set_errno((char *)tok->next->content);
	if (block->fd_out > 2)
		close(block->fd_out);
	block->fd_out = fd;
	return (SUCCESS);
}

t_ert	open_append_in(t_instruction_block_tree *block, t_string_token *tok, char **env)
{
	int fd;

	(void)env;
	fd = open(tok->next->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		per_n_set_errno((char *)tok->next->content);
	if (block->fd_out > 2)
		close(block->fd_out);
	block->fd_out = fd;
	return (SUCCESS);
}
