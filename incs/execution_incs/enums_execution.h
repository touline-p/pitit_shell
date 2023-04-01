/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums_execution.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:28:34 by wangthea          #+#    #+#             */
/*   Updated: 2023/03/23 12:00:28 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_EXECUTION_H
# define ENUMS_EXECUTION_H

/*---- typedef enums ---------------------------------------------------------*/

typedef enum e_token_minishell	t_token_minishell;
typedef enum e_secured_status	t_secured_status;

/*----------------------------------------------------------------------------*/

# ifndef EMT
#  define EMT

enum	e_token_minishell
{
	START,
	PIPE,
	AMPERSAND,
	CHEVRON_IN,
	CHEVRON_OUT,
	OR,
	AND,
	HERE_DOC,
	APPENDS,
	O_PRTSS,
	C_PRTSS,
	SEMICOLON,
	E_SPACE,
	TABULATION,
	LETTER,
	EOL,
	STRING,
	DOLLAR,
	NONE
};

# endif

#endif
