/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums_execution.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:28:34 by wangthea          #+#    #+#             */
/*   Updated: 2023/05/03 11:40:34 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_EXECUTION_H
# define ENUMS_EXECUTION_H

/*---- typedef enums ---------------------------------------------------------*/

typedef enum e_token_minishell	t_token_minishell;
typedef enum e_builtin			t_builtin;

/*----------------------------------------------------------------------------*/

enum e_builtin
{
	CMD,
	ENV,
	ECHO_,
	EXPORT,
	PWD,
	EXIT,
	UNSET,
	CD,
	EMPTY
};

#endif
