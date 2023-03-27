/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_execution.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 19:17:36 by wangthea          #+#    #+#             */
/*   Updated: 2023/03/27 17:50:12 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_EXECUTION_H
# define STRUCTURES_EXECUTION_H

# include "enums_execution.h"

/*---- typedef structures ----------------------------------------------------*/

typedef struct s_string_token	t_string_token;
typedef struct s_data			t_data;	

/*---- structures ------------------------------------------------------------*/

struct s_string_token
{
	t_token_minishell	token;
	char				*content;
	t_string_token		*next;
};

struct s_data
{
	char	***commands;
	int		nb_of_pipes;
	int		nb_of_commands;
	int		**fds;
	pid_t	*process_ids;
	int		infile;
	int		outfile;
};


#endif