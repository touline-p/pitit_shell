/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:54:36 by wangthea          #+#    #+#             */
/*   Updated: 2023/03/23 13:43:08 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

/***
typedef struct s_process
{
	int fd_in;
	int fd_out;
	char *cmd;
	char **args;
}	t_process;

 ***/

/***
< start > < 1str > <_>_> < 2str > < 3str > < << > < 4str > < 5str > < end >

< start > < cmd > < > > < out_file > < argument1 > < << > < endfile > < argument2 > < end >

< cmd > < arg1 > < arg2 > < NULL >

"cmd > outfile arg1 < infile arg2 | cmd args args"
"cmd arg1 arg2"

echo you > infile damn | cat this >> la dici

<echo> < you> <damn> <|> <cat> <this> <dici> <endl>

action 1

infile = stdin  && outfile = fd:infile;
cmd : echo -> builtin -> echo_builtin(structure, env_pt);
args : {"echo", "you", "damn", NULL};

pipe {};

action 2

infile = pipe[0]  && outfile = fd:la(open avec le flag O_append);
cmd = cat; -> pas builtin -> go path -> /bin/cat
args = {"cat", "this", "dici", NULL};
execve(cmd, args, *env_pt);

***/

static void	token_recognition(t_string_token *string_of_tokens)
{
	//check des chevrons	-> infile / outifile - les gerer - les virer
	//check here_docs 		-> here_doc becomes infile 
	//check des pipes		-> checks fds -> prepare for fork
	//check commands 		-> builtins -> call built_in function
	//						-> commands to exec -> get_path, ... pipex
}

void	execution(t_string_token *tokens)
{
	token_recognition(tokens);
}
