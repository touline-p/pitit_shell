/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_here_doc_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <bpoumeau@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 23:14:22 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/03/12 01:13:24 by bpoumeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parsing.h"

//static int _read_here_doc_and_ret_fd(char *str, char **env);

t_ert	get_here_doc_fd(t_instruction_block_tree *block, t_string_token *tok, char **env)
{
	int fd;

	(void)env;
	//fd = read_here_doc_and_ret_fd(tok->next->content, env);
	fd = 0;
	if (fd == -1)
		per_n_set_errno((char *)tok->next->content);
	if (block->fd_out > 2)
		close(block->fd_out);
	block->fd_out = fd;
	return (SUCCESS);
}

