/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <bpoumeau@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 00:07:39 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/03/12 00:41:40 by bpoumeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parsing.h"

static void	_init_first_child_fds(t_instruction_block_tree *first_block);

t_ert	allocate_first_child_on(t_string_token **str_tok_pt, t_instruction_block_tree **block_pt, int **pipe_arr, char **env)
{
	(void)str_tok_pt;
	*block_pt = instruction_block_tree_constructor();
	if (*block_pt == NULL)
		return (MLC_ERR);
	_init_first_child_fds(*block_pt);
	if (next_control_operator_is_a_pipe((*str_tok_pt)->next))
		(*block_pt)->fd_out = pipe_arr[0][1];
	stock_last_redirect(*block_pt, *str_tok_pt, env);
	return (SUCCESS);
}

static void	_init_first_child_fds(t_instruction_block_tree *first_block)
{
	first_block->fd_in = STDIN_FILENO;
	first_block->fd_out = STDOUT_FILENO;
}