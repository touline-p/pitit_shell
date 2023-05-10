/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_parsing.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 19:17:36 by wangthea          #+#    #+#             */
/*   Updated: 2023/03/21 18:19:19 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_PARSING_H
# define STRUCTURES_PARSING_H

# include "enums_parsing.h"

/*---- typedef structures ----------------------------------------------------*/

typedef struct s_token	t_token;
typedef struct s_block	t_block;

/*---- structures ------------------------------------------------------------*/

typedef enum e_secured
{
	SECURED,
	UNSECURED
}	t_esec;

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

#endif
