/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_execution.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 19:17:36 by wangthea          #+#    #+#             */
/*   Updated: 2023/03/22 16:14:10 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_EXECUTION_H
# define STRUCTURES_EXECUTION_H

/*---- typedef structures ----------------------------------------------------*/

typedef struct s_execution  t_execution;
typedef struct s_process    t_process;

/*---- structures ------------------------------------------------------------*/

struct s_process
{
	char	**command;
	char	**args;
	int		fd_in;
	int		fd_out;
};

struct s_execution
{
	t_process	process;
	int			nb_of_commands;
};

#endif