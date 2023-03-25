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

typedef enum e_return_status	t_return_status;
typedef enum e_token_minishell	t_token_minishell;
typedef enum e_secured_status	t_secured_status;

/*----------------------------------------------------------------------------*/

enum	e_return_status
{
	SUCCESS = 0,
	FAILURE = 1,
	FAILED_MALLOC = 2,
	FAILED_WRITE = 4
};

enum	e_secured_status
{
	SECURED,
	UNSECURED
};

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
	SPACE,
	TABULATION,
	LETTER,
	EOL,
	STRING,
	DOLLAR,
	NONE
};

#endif