/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:54:36 by wangthea          #+#    #+#             */
/*   Updated: 2023/03/27 18:46:28 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

/*---- prototypes ------------------------------------------------------------*/

static void	token_recognition(t_data *data, t_string_token *string_of_tokens);
static void	files_management(t_data *data, char *file, t_token_minishell token);

/*----------------------------------------------------------------------------*/

void	execution(t_string_token *string_of_tokens)
{
	t_data	data;
	
	ft_memset(&data, 0, sizeof(t_data));
	token_recognition(&data, string_of_tokens);
}

static void	token_recognition(t_data *data, t_string_token *string_of_tokens)
{
	t_string_token	*temp;
	t_token_minishell token;

	temp = string_of_tokens;
	while (temp != NULL)
	{
		if (temp->token == PIPE)
			data->nb_of_pipes++;
		else if (temp->token == CHEVRON_IN || temp->token == CHEVRON_OUT || \
			temp->token == APPENDS)
		{
			token = temp->token;
			temp = temp->next;
			files_management(data, temp->content, token);
		}
		else if (temp->token == HERE_DOC)
			puts("here_doc");
		temp = temp->next;
	}
}

static void	files_management(t_data *data, char *file, t_token_minishell token)
{
	printf("%d\n", token);
	if (token == CHEVRON_IN)
	{
		puts("che_in");
		if (data->infile != 0)
			close(data->infile);
		data->infile = open(file, O_RDONLY, 0644);
		if (data->infile == -1)
			perror("open infile");
	}
	else 
	{
		if (data->outfile != 0)
			close(data->outfile);
		if (token == CHEVRON_OUT)
		{
			puts("che_out");
			data->outfile = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		else
		{
			puts("append");
			data->outfile = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		if (data->outfile == -1)
			perror("open outfile");
	}
}
	/// balader dans la liste chainees et faire en fonction
	//create structure init -> fds management	-> fork management -> heredoc 
	//check des chevrons	-> infile / outifile - les gerer - les virer
	//check here_docs 		-> here_doc becomes infile 
	//check des pipes		-> checks fds -> prepare for fork
	//check commands 		-> builtins -> call built_in function
	//						-> commands to exec -> get_path, ... pipex