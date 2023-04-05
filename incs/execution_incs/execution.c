/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:54:36 by wangthea          #+#    #+#             */
/*   Updated: 2023/03/29 18:22:32 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

/*---- prototypes ------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/

void	execution(t_string_token *string_of_tokens)
{
	t_data	data;
	
	ft_memset(&data, 0, sizeof(t_data));
	token_recognition(&data, string_of_tokens);
}

	/// balader dans la liste chainees et faire en fonction
	//create structure init -> fds management	-> fork management -> heredoc
	//check des chevrons	-> infile / outifile - les gerer - les virer
	//check here_docs 		-> here_doc becomes infile 
	//check des pipes		-> checks fds -> prepare for fork
	//check commands 		-> builtins -> call built_in function
	//						-> commands to exec -> get_path, ... pipex