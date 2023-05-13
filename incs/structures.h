/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangthea <wangthea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 23:59:25 by wangthea          #+#    #+#             */
/*   Updated: 2023/05/14 00:06:23 by wangthea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

/*---- headers ---------------------------------------------------------------*/

# include "enums.h"

/*---- typedef structures ----------------------------------------------------*/

typedef struct s_token	t_token;
typedef struct s_block	t_block;

typedef struct s_string_token	t_string_token;
typedef struct s_data			t_data;
typedef struct s_cmd			t_cmd;

typedef struct s_list_of_char	t_lstc;

/*---- structures ------------------------------------------------------------*/

struct	s_token
{
	t_emt			token;
	char			sign_char;
	void			*content;
	t_esec			esec;
	struct s_token	*next;
	struct s_token	*next_word;
};

struct	s_block
{
	int		value;
	t_e_op	e_op;
	t_block	*right;
	t_block	*left;
};

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
	int				index;
	char			*prompt;
	int				fd[2];
	int				nb_of_pipe;
};

struct s_cmd
{
	t_builtin	id_command;
	int			infile;
	int			outfile;
	int			fd_hd[2];
	char		**commands;
	char		*heredoc_data;
	bool		is_heredoc;
	bool		is_ambiguous;
	pid_t		process_id;
};

struct	s_list_of_char
{
	t_lstc	*next;
	char	c;
};


#endif