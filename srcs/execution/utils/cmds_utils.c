/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:34:06 by twang             #+#    #+#             */
/*   Updated: 2023/05/04 13:54:02 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

t_builtin	is_builtin(char *string)
{
	t_builtin	ret_val;
	const char	*name_arr[] = {NULL, "env","echo", "export", \
							"pwd","exit", "unset", "cd", ""};
	ret_val = ENV;
	if (!string)
		return (CMD);
	while (ret_val < 8)
	{
		if (ft_strcmp(string, (char *)name_arr[ret_val]) == 0)
			return (ret_val);
		ret_val++;
	}
	return (CMD);
}

t_return_status	builtin_switch(t_cmd command, char **av, char ***env_pt)
{
	const t_builtin_ft	ft_arr[] = {NULL, &env_builtin, &echo_builtin, \
									&export_builtin, &pwd_builtin, \
									&exit_builtin, &unset_builtin, \
									&cd_builtin};
	t_return_status	ret_val;

	ret_val = (*ft_arr[command.id_command])(av, env_pt);
	if (command.infile > 2)
		close(command.infile);
	if (command.outfile > 2)
		close(command.outfile);
	return (ret_val);
}

bool	is_path(char *line)
{
	return (ft_strchr(line, '/') != NULL);
}

bool	is_cmd(char *line)
{
	return (ft_strchr(line, '/') == NULL);
}
