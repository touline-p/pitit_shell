/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangthea <wangthea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:54:36 by wangthea          #+#    #+#             */
/*   Updated: 2023/04/06 23:40:32 by wangthea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

/*---- prototypes ------------------------------------------------------------*/

static void	cmds_block_alloc(t_data *data, t_string_token *string_of_tokens);

/*----------------------------------------------------------------------------*/

void	execution(t_string_token *string_of_tokens)
{
	t_data	data;

	display_str_token(string_of_tokens);
	ft_bzero(&data, sizeof(t_data));
	cmds_block_alloc(&data, string_of_tokens);
	infiles_management(&data, string_of_tokens);
	outfiles_management(&data, string_of_tokens);
	clean_files_token(string_of_tokens);
	clean_token(string_of_tokens);
	/*command_management(string_of_tokens);
	 token_recognition(&data, string_of_tokens);*/
}

static void	cmds_block_alloc(t_data *data, t_string_token *string_of_tokens)
{
	t_string_token	*temp;

	temp = string_of_tokens;
	while (temp != NULL)
	{
		if (temp->token == PIPE)
			data->nb_of_cmd++;
		printf("%s\n", string_of_tokens->content);
		temp = temp->next;
	}
	printf("number of commands is : %d\n", data->nb_of_cmd);
	data->cmds_block = (t_cmd *)malloc((data->nb_of_cmd + 1) * sizeof(t_cmd));
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
	
	

	balader dans la liste chainees et faire en fonction
	create structure init -> fds management	-> fork management -> heredoc
	check des chevrons	-> infile / outifile - les gerer - les virer
	check here_docs 	-> here_doc becomes infile 
	check des pipes		-> checks fds -> prepare for fork
	check commands 		-> builtins -> call built_in function
						-> commands to exec -> get_path, ... pipex

*/