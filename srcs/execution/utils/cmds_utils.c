/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:34:06 by twang             #+#    #+#             */
/*   Updated: 2023/04/12 19:27:24 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

t_builtin	is_builtin(char *string)
{
	const char	*name_arr[] = {NULL, "env","echo", "export", \
							"exit", "unset", "cd", "pwd"};
	t_builtin	ret_val;

	ret_val = ENV;
	while (ret_val < 8)
	{
		if (ft_strcmp(string, (char *)name_arr[ret_val]) == 0)
			return (ret_val);
		ret_val++;
	}
	return (CMD);
}

t_return_status 	builtin_switchman(t_builtin builtin, char **av, char ***env_pt)
{
	const t_builtin_ft	ft_arr[] = {NULL, &env_builtin, &echo_builtin, &export_builtin,
									NULL, &unset_builtin, &cd_builtin, &pwd_builtin};
	
	return ((*ft_arr[builtin])(av, env_pt));
}