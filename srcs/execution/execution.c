/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:54:36 by wangthea          #+#    #+#             */
/*   Updated: 2023/04/13 16:24:24 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

/*---- prototypes ------------------------------------------------------------*/

static t_return_status	alloc_cmd_block(t_data *data, \
t_string_token *str_of_tok);

/*----------------------------------------------------------------------------*/

void	execution(t_string_token *str_of_tok, char ***env_pt)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	alloc_cmd_block(&data, str_of_tok);
	infiles_management(&data, str_of_tok);
	outfiles_management(&data, str_of_tok);
	clean_files_token(str_of_tok);
	clean_token(str_of_tok);
	strings_management(&data, str_of_tok, *env_pt);
	builtin_switch(data.cmds_block->id_command, data.cmds_block->commands, env_pt);
	string_token_destructor(str_of_tok);
}

static t_return_status	alloc_cmd_block(t_data *data, \
t_string_token *str_of_tok)
{
	t_string_token	*temp;

	temp = str_of_tok;
	while (temp != NULL)
	{
		if (temp->token == PIPE)
			data->nb_of_pipe++;
		temp = temp->next;
	}
	data->cmds_block = (t_cmd *)ft_calloc((data->nb_of_pipe + 2), sizeof(t_cmd));
	if (!data->cmds_block)
		return (FAILED_MALLOC);
	ft_bzero(data->cmds_block, sizeof(t_cmd));
	return (SUCCESS);
}

	/*
	< infile cat -e | cat | cat > outfile
	
	data->cmds_block[0]->command = "cat" "-e"
	data->cmds_block[0]->infile = fd_in
	data->cmds_block[0]->outfile = -1
	data->cmds_block[0]->pipes[2] = ignore

	data->cmds_block[1]->command = "cat"
	data->cmds_block[1]->infile = -1
	data->cmds_block[1]->outfile = -1
	data->cmds_block[1]->pipes[2] = ignore

	data->cmds_block[2]->command = "cat"
	data->cmds_block[2]->infile = -1
	data->cmds_block[2]->outfile = fd_out
	data->cmds_block[2]->pipes[2] = ignore
	
	check lst_tokens
	check chevrons		-> infile / here_doc
						-> expand to here_doc
						-> outfile / append
	check commands 		-> recup commandes + args
						-> add path
						-> check fds -> standart -> pipes ...
						-> builtins -> call built_in function
						-> exec command
*/