/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangthea <wangthea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 23:50:46 by wangthea          #+#    #+#             */
/*   Updated: 2023/05/13 23:53:30 by wangthea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*---- libraries -------------------------------------------------------------*/

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>
# include <dirent.h>

# include "libft.h"

/*---- program headers -------------------------------------------------------*/

# include "defines.h"
# include "enums.h"
# include "prototypes.h"
# include "structures.h"

/*---- global variable -------------------------------------------------------*/

extern int	g_ret_val;

#endif
