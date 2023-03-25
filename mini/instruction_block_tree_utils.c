/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_block_tree_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <bpoumeau@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:04:39 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/03/10 19:16:18 by bpoumeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parsing.h"

t_instruction_block_tree	*instruction_block_tree_constructor(void)
{
	t_instruction_block_tree	*new;

	new = malloc(sizeof(t_instruction_block_tree));
	if (new == NULL)
		return (NULL);
	new->next = NULL;
	new->sub_block = NULL;
	new->cmd = NULL;
	new->args = NULL;
	new->fd_in = -1;
	new->fd_out = -1;
	return (new);
}

t_ert	instruction_block_tree_constructor_on(t_instruction_block_tree **instr_pt)
{
	*instr_pt = instruction_block_tree_constructor();
	if (*instr_pt == NULL)
		return (MLC_ERR);
	return (SUCCESS);
}

void	instruction_block_tree_destructor(t_instruction_block_tree *trash)
{
	if (trash == NULL)
		return ;
	instruction_block_tree_destructor(trash->sub_block);
	instruction_block_tree_destructor(trash->next);
	ft_free_split(trash->args);
	free(trash->cmd);
	free(trash);
}