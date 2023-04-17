/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines_execution.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:27:48 by wangthea          #+#    #+#             */
/*   Updated: 2023/04/12 19:10:52 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_EXECUTION_H
# define DEFINES_EXECUTION_H

# define MINI_SHELL_MUST_GO_ON 1
# define HEREDOC_MUST_GO_ON 1
# define STRT_CHR -1
# define EOSTR 0
# define METACHAR_SET "|&<>(); "
# define IFS " \t\n"

typedef t_return_status (*t_builtin_ft)(char **av, char ***env_pt);

#endif 