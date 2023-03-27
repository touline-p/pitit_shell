/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:54:36 by wangthea          #+#    #+#             */
/*   Updated: 2023/03/27 14:59:30 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

/*---- prototypes ------------------------------------------------------------*/

static void	token_recognition(t_string_token *string_of_tokens);

/*----------------------------------------------------------------------------*/

void	execution(t_string_token *string_of_tokens)
{
	token_recognition(string_of_tokens);
}

static void	token_recognition(t_string_token *string_of_tokens)
{
	t_string_token	*temp;

	temp = string_of_tokens;
	while (temp != NULL)
	{
		if (temp->token == START)
			puts("start");
		if (temp->token == PIPE)
			puts("pipe");
		if (temp->token == CHEVRON_IN)
			puts("chevron_in");
		if (temp->token == CHEVRON_OT)
			puts("chevron_out");
		if (temp->token == HERE_DOC)
			puts("here_doc");
		if (temp->token == APPENDS)
			puts("appends");
		puts("passe a la casse");
		temp = temp->next;
	}
}
	/// balader dans la liste chainees et faire en fonction
	//create structure init -> fds management	-> fork management -> heredoc 
	//check des chevrons	-> infile / outifile - les gerer - les virer
	//check here_docs 		-> here_doc becomes infile 
	//check des pipes		-> checks fds -> prepare for fork
	//check commands 		-> builtins -> call built_in function
	//						-> commands to exec -> get_path, ... pipex