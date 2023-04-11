/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execution.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:11:55 by twang             #+#    #+#             */
/*   Updated: 2023/04/11 15:59:05 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXECUTION_H
# define MINISHELL_EXECUTION_H

/*---- libraries -------------------------------------------------------------*/

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft.h"

#include "../srcs/debug_folder/debug.h"

/*---- includes --------------------------------------------------------------*/

# include "defines_execution.h"
# include "enums_parsing.h"
# include "prototypes_execution.h"
# include "structures_execution.h"

/*---- global ----------------------------------------------------------------*/

extern int	g_ret_val;

#endif