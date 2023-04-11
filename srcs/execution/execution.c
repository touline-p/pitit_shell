/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:54:36 by wangthea          #+#    #+#             */
/*   Updated: 2023/04/11 18:34:53 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

/*---- prototypes ------------------------------------------------------------*/

static void	cmds_block_alloc(t_data *data, t_string_token *string_of_tokens);

/*----------------------------------------------------------------------------*/

void	execution(t_string_token *string_of_tokens)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	cmds_block_alloc(&data, string_of_tokens);
	infiles_management(&data, string_of_tokens);
	outfiles_management(&data, string_of_tokens);
	clean_files_token(string_of_tokens);
	clean_token(string_of_tokens);
	display_str_token(string_of_tokens);
	strings_management(&data, string_of_tokens);
	string_token_destructor(string_of_tokens);
}

static void	cmds_block_alloc(t_data *data, t_string_token *string_of_tokens)
{
	t_string_token	*temp;

	temp = string_of_tokens;
	while (temp != NULL)
	{
		if (temp->token == PIPE)
			data->nb_of_pipe++;
		temp = temp->next;
	}
	data->cmds_block = (t_cmd *)malloc((data->nb_of_pipe + 1) * sizeof(t_cmd));
	ft_bzero(data->cmds_block, sizeof(t_cmd));
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
	
	check lst_tokens :
	check chevrons		-> infile / here_doc
						-> expand to here_doc
						-> outfile / append
	check commands 		-> recup commandes + args
						-> add path
						-> check fds -> standart -> pipes ...
						-> builtins -> call built_in function
						-> exec command
*/