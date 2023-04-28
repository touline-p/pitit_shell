/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:34:06 by twang             #+#    #+#             */
/*   Updated: 2023/04/28 15:18:30 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

t_builtin	is_builtin(char *string)
{
	t_builtin	ret_val;
	const char	*name_arr[] = {NULL, "env","echo", "export", \
							 "pwd","exit", "unset", "cd"};

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

t_return_status 	builtin_switch(t_builtin builtin, char **av, char ***env_pt, t_data *data)
{
	const t_builtin_ft	ft_arr[] = {NULL, &env_builtin, &echo_builtin, \
									&export_builtin, &pwd_builtin, &exit_builtin, &unset_builtin, \
									&cd_builtin};
									
	if (builtin == CMD)
		return (FAILURE);
	return ((*ft_arr[builtin])(av, env_pt, data));
}

bool	is_path(char *line)
{
	return (ft_strchr(line, '/') != NULL);
}

bool	is_cmd(char *line)
{
	return (ft_strchr(line, '/') == NULL);
}

#ifdef TST_IS_CMD

int main()
{
	printf("cmd : %d\npaths : %d\n", is_cmd("minishell"), is_cmd("./minishell"));
}

#endif
