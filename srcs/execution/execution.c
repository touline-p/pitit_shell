/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:54:36 by wangthea          #+#    #+#             */
/*   Updated: 2023/04/05 20:13:28 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

/*---- prototypes ------------------------------------------------------------*/

static void	init_struct(t_data *data);

/*----------------------------------------------------------------------------*/

void	execution(t_string_token *string_of_tokens)
{
	t_data	data;

	init_struct(&data);
	fill_struct(&data, string_of_tokens);
	// token_recognition(&data, string_of_tokens);
}

static void	init_struct(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	ft_bzero(data->cmds_block, sizeof(t_cmd));
}

	/// balader dans la liste chainees et faire en fonction
	//create structure init -> fds management	-> fork management -> heredoc
	//check des chevrons	-> infile / outifile - les gerer - les virer
	//check here_docs 		-> here_doc becomes infile 
	//check des pipes		-> checks fds -> prepare for fork
	//check commands 		-> builtins -> call built_in function
	//						-> commands to exec -> get_path, ... pipex