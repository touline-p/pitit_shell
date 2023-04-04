/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums_parsing.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:28:34 by wangthea          #+#    #+#             */
/*   Updated: 2023/04/04 17:35:23 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_PARSING_H
# define ENUMS_PARSING_H

/*---- typedef enums ---------------------------------------------------------*/

typedef enum	e_token_minishell	t_emt;
typedef enum	e_enum_op			t_e_op;

/*----------------------------------------------------------------------------*/

#undef SPACE
# ifndef EMT
#  define EMT
enum 	e_token_minishell
{
	START = 0,
	PIPE = 1,
	AMPERSAND = 2,
	CHEVRON_IN = 3,
	CHEVRON_OT = 4,
	OR = 5,
	AND = 6,
	HERE_DOC = 7,
	APPENDS = 8,
	O_PRTSS = 9,
	C_PRTSS = 10,
	SEMICOLON = 11,
	E_SPACE = 12,
	TABULATION = 13,
	LETTER = 14,
	EOL = 15,
	STRING = 16,
	DOLLAR = 17,
	NONE = 18
};
# endif

enum e_enum_op
{
	AND_OP = 1,
	OR_OP = 2,
	UNRESOLVED = 3,
	RESOLVED = 4
};

#endif
