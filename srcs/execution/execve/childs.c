/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:17:52 by twang             #+#    #+#             */
/*   Updated: 2023/04/19 16:47:57 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

/*---- prototypes ------------------------------------------------------------*/

static char	*add_path_cmd(int block_id, t_data *data, char **env);

/*----------------------------------------------------------------------------*/

////to do the piiipe
t_return_status	childs_execve(t_data *data, char **env)
{
	int		block_id;
	char	*command;

	block_id = 0;
	while (block_id < data->nb_of_pipe + 1)
	{
		data->cmds_block[block_id].process_id = fork();
		if (data->cmds_block[block_id].process_id == 0)
		{
			duplicate_fds(data, block_id);
			command = add_path_cmd(block_id, data, env);
			execve(command, data->cmds_block[block_id].commands, env);
			exit(FAILURE);
		}
		else if (data->cmds_block[block_id].process_id < 0)
		{
			ft_dprintf(2, RED"Fork Issue: Resource temporarily unavailable\n"END);
			break ;
		}
		block_id++;
	}
	return (SUCCESS);
}

static char	*add_path_cmd(int block_id, t_data *data, char **env)
{
	int		i;
	char	**paths;

	if (access(data->cmds_block[block_id].commands[0], X_OK) == 0)
		return (data->cmds_block[block_id].commands[0]);
	paths = get_paths(env);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		paths[i] = strjoin_path_cmd(paths[i], data->cmds_block[block_id].commands[0]);
		if (!paths[i])
		{
			ft_free((void **)paths, get_path_size(paths));
			return (NULL);
		}
		if (access(paths[i], X_OK) == 0)
		{
			data->cmds_block[block_id].commands[0] = ft_strdup(paths[i]);
			ft_free((void **)paths, get_path_size(paths));
			return (data->cmds_block[block_id].commands[0]);
		}
		i++;
	}
	return (NULL);
}
