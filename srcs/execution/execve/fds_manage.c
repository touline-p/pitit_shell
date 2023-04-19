/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangthea <wangthea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:26:01 by twang             #+#    #+#             */
/*   Updated: 2023/04/19 14:55:57 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"
/*
void	close_fds(t_data *data, int block_id)
{
	int	i;

	i = 0;
	while (i < data->nb_of_pipe)
	{
		if (i != block_id - 1)
			close(data->cmds_block[block_id].fd_hd[0]);
		if (i != block_id)
			close(data->cmds_block[block_id].fd_hd[1]);
		i++;
	}
}

void	close_all_fds(t_data *data, int block_id)
{
}
 */

static	t_return_status _dup_n_close(int to_dup, int to_replace)
{
	if (to_dup == to_replace)
		return (SUCCESS);
	if (dup2(to_dup, to_replace) == -1)
		return (FAILURE);
	return (SUCCESS);
}

t_return_status 	duplicate_fds(t_data *data, int block_id)
{
	t_cmd	block;

	block = data->cmds_block[block_id];
	print_cmd_block("dup",block);
	if (_dup_n_close(block.infile, STDIN_FILENO) != SUCCESS
		|| _dup_n_close(block.outfile, STDOUT_FILENO) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

// #define TST_DUP_FD
#ifdef TST_DUP_FD
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
			printf(BLUE"command without paths? %s\n"END, data->cmds_block[block_id].commands[0]);
			data->cmds_block[block_id].commands[0] = ft_strdup(paths[i]);
			printf(BLUE"command with paths? %s\n"END, data->cmds_block[block_id].commands[0]);
			ft_free((void **)paths, get_path_size(paths));
			return (data->cmds_block[block_id].commands[0]);
		}
		i++;
	}
	return (NULL);
}

int	main(int ac, char **av, char **env)
{
	int	block_id = 0;
	t_cmd	cmd = {
		.infile = open(av[1], O_RDONLY),
		.outfile = open(av[3], O_WRONLY | O_CREAT | O_TRUNC, 0644),
		.commands = ft_split(av[2], ' ')
	};
	t_data	data = {
		.cmds_block = &cmd,
		.nb_of_pipe = 0
	};
	
	duplicate_fds(&data, block_id);
	if (ac)
		execve(add_path_cmd(0, &data, env),cmd.commands, env);
	return (0);
}
#endif