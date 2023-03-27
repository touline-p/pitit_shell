/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_block_chain.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <bpoumeau@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:32:06 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/03/11 00:25:15 by bpoumeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parsing.h"

static	t_ert	_str_tok_to_instr_ep(t_ert ret_val);

t_ert	str_token_to_instruction_block_tree_on(t_string_token *tok, t_instruction_block_tree **tree_pt)
{
	int				**pipe_arr;
	//t_string_token	*pin;
	(void)tree_pt;

	//pin = tok;
	if (init_pipe_arr_on(&pipe_arr, tok) != SUCCESS)
		return (FAILURE);
	//if (allocate_first_child_on(&pin, tree_pt) != SUCCESS)
	return (_str_tok_to_instr_ep(SUCCESS));
}

static	t_ert	_str_tok_to_instr_ep(t_ert ret_val)
{
	return (ret_val);
}
