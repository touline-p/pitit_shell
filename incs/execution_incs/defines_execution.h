/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines_execution.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:27:48 by wangthea          #+#    #+#             */
/*   Updated: 2023/05/16 17:34:04 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_EXECUTION_H
# define DEFINES_EXECUTION_H

# define MINI_SHELL_MUST_GO_ON 1
# define HEREDOC_MUST_GO_ON 1
# define STRT_CHR -1
# define EOSTR 0
# define IFS " \t\n"
# define PROMPT_MESSAGE " - Y a quoi : "
# define START_MSG_00 "\n--------------------------------------------------"
# define START_MSG_01 "----------------------------\t\n"
# define START_MSG_02 " __    __   __   __   __   __   ______   __  __   __"
# define START_MSG_03 "____   __       __        \n"
# define START_MSG_04 "/\\ \"-./  \\ /\\ \\ /\\ \"-.\\ \\ /\\ \\ /\\  ___\\"
# define START_MSG_05 " /\\ \\_\\ \\ /\\  ___\\ /\\ \\     /\\ \\       \n"
# define START_MSG_06 "\\ \\ \\-./\\ \\\\ \\ \\\\ \\ \\-.  \\\\ \\ \\\\ \\_"
# define START_MSG_07 "__  \\\\ \\  __ \\\\ \\  __\\ \\ \\ \\____\\ \\ \\__"
# define START_MSG_08 "__  \n"
# define START_MSG_09 " \\ \\_\\ \\ \\_\\\\ \\_\\\\ \\_\\\\\"\\_\\\\ \\_\\"
# define START_MSG_10 "\\/\\_____\\\\ \\_\\ \\_\\\\ \\_____\\\\ \\_____\\\\ "
# define START_MSG_11 "\\_____\\ \n"
# define START_MSG_12 "  \\/_/  \\/_/ \\/_/ \\/_/ \\/_/ \\/_/ \\/_____/ \\/_"
# define START_MSG_13 "/\\/_/ \\/_____/ \\/_____/ \\/_____/ \n"
# define START_MSG_14 "\t\t\t\t\t\t by ⭐ bpoumeau & twang ⭐\n\n"

typedef t_return_status	(*t_builtin_ft)(char **av, char ***env_pt);

#endif 