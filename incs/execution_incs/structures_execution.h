/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_execution.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 19:17:36 by wangthea          #+#    #+#             */
/*   Updated: 2023/05/17 13:11:48 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_EXECUTION_H
# define STRUCTURES_EXECUTION_H

# include "enums_execution.h"

/*---- typedef structures ----------------------------------------------------*/

typedef struct s_string_token	t_string_token;
typedef struct s_data			t_data;
typedef struct s_cmd			t_cmd;
typedef struct s_data			t_data;
typedef struct s_cmd			t_cmd;

typedef struct s_wild_data		t_w_data;
typedef struct s_list_of_char	t_lstc;
typedef t_return_status	(*t_files_manage_ft)(t_data *data, \
										char **line, int i, char **env);

/*---- structures ------------------------------------------------------------*/

struct s_string_token
{
	t_token_minishell	token;
	char				*content;
	char				**str_arr;
	t_string_token		*next;
};

struct s_data
{
	t_cmd			*cmds_block;
	t_string_token	**instructions_arr;
	struct termios	term;
	int				index;
	char			*prompt;
	int				fd[2];
	int				nb_of_pipe;
};

struct s_cmd
{
	t_builtin	id_command;
	char		**commands;
	char		*heredoc_data;
	bool		is_ambiguous;
	bool		is_heredoc;
	int			infile;
	int			outfile;
	int			fd_hd[2];
	pid_t		process_id;
};

struct	s_list_of_char
{
	t_lstc	*next;
	char	c;
};

#endif