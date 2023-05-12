/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines_execution.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:27:48 by wangthea          #+#    #+#             */
/*   Updated: 2023/05/12 17:28:55 by twang            ###   ########.fr       */
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

# define PROMPT_00 "------------------------------------------------------------------------------"
# define PROMPT_01 " __    __   __   __   __   __   ______   __  __   ______   __       __        "
# define PROMPT_02 "/\\ \"-./  \\ /\\ \\ /\\ \"-.\\ \\ /\\ \\ /\\  ___\\ /\\ \\_\\ \\ /\\  ___\\ /\\ \\     /\\ \\       "
# define PROMPT_03 "\\ \\ \\-./\\ \\\\ \\ \\\\ \\ \\-.  \\\\ \\ \\\\ \\___  \\\\ \\  __ \\\\ \\  __\\ \\ \\ \\____\\ \\ \\____  "
# define PROMPT_04 " \\ \\_\\ \\ \\_\\\\ \\_\\\\ \\_\\\\\"\\_\\\\ \\_\\\\/\\_____\\\\ \\_\\ \\_\\\\ \\_____\\\\ \\_____\\\\ \\_____\\ "
# define PROMPT_05 "  \\/_/  \\/_/ \\/_/ \\/_/ \\/_/ \\/_/ \\/_____/ \\/_/\\/_/ \\/_____/ \\/_____/ \\/_____/ "
# define PROMPT_06 "------------------------------------------------------------------------------"
# define PROMPT_07 "\e]8;;https://profile.intra.42.fr/users/bpoumeau\a\e[34mbpoumeau\e[34m\e]8;;\a "
# define PROMPT_08 "\e]8;;https://profile.intra.42.fr/users/twang\a\e[34mtwang\e[34m\e]8;;\a "


typedef t_return_status	(*t_builtin_ft)(char **av, char ***env_pt);

#endif 