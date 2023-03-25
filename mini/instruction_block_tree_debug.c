/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_block_tree_debug.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <bpoumeau@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 23:40:12 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/03/09 23:52:57 by bpoumeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_mini.h"

void	display_instruction_block_tree(t_instruction_block_tree *tree, int sub_depth)
{
	int i = 0;
	printf("sub_depth : %d\n", sub_depth);
	while (tree)
	{
		printf("node %d\n", i);
		i++;
		printf("fd_in : %d\n", tree->fd_in);
		printf("fd_out : %d\n", tree->fd_out);
		printf("cmd %s", tree->cmd);
		printf("args : \n");
		ft_print_split(tree->args);
		printf("\n");
		if (tree->sub_block)
			display_instruction_block_tree(tree->sub_block, sub_depth + 1);
		tree = tree->next;
	}
}
