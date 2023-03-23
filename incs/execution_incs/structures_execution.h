/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_execution.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 19:17:36 by wangthea          #+#    #+#             */
/*   Updated: 2023/03/23 12:27:15 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_EXECUTION_H
# define STRUCTURES_EXECUTION_H

# include "enums_execution.h"

/*---- typedef structures ----------------------------------------------------*/

typedef struct s_token_identity			t_token_identity;
typedef struct s_string_token			t_string_token;
typedef struct s_instruction_block_tree	t_instruction_block_tree;

/*---- structures ------------------------------------------------------------*/

struct	s_token_identity
{
	t_token_minishell	token;
	t_secured_status	secured_status;
	char				sign_char;
	void				*content;
	t_token_identity	*next;
	t_token_identity	*next_word;
};

struct s_string_token
{
	t_token_minishell	token;
	char				*content;
	t_string_token		*next;
};

struct	s_instruction_block_tree
{
	t_instruction_block_tree	*next;
	t_instruction_block_tree	*sub_block;
	char						**args;
	char						*cmd;
	int							fd_in;
	int							fd_out;
};

#endif