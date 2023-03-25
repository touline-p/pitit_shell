/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_execution.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 19:17:36 by wangthea          #+#    #+#             */
/*   Updated: 2023/03/23 17:19:35 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_EXECUTION_H
# define STRUCTURES_EXECUTION_H

# include "enums_execution.h"

/*---- typedef structures ----------------------------------------------------*/

typedef struct s_string_token			t_string_token;

/*---- structures ------------------------------------------------------------*/

struct s_string_token
{
	t_token_minishell	token; //identite 
	char				*content;
	t_string_token		*next;
};


#endif