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
static t_return_status _do_the_pipe(t_cmd *cmd_block, int nb_of_pipe, int block_id);
static void 			_manage_the_pipe(t_data *data, int block_id);

/*----------------------------------------------------------------------------*/

////to do the piiipe

void close_this(int fd)
{
	if (fd > 2)
		close(fd);
}

t_return_status	childs_execve(t_data *data, char **env)
{
	int		block_id;
	char	*command;

	block_id = 0;
	while (block_id < data->nb_of_pipe + 1)
	{
		if (_do_the_pipe(&(data->cmds_block[block_id]), data->nb_of_pipe, block_id) != SUCCESS)
			return (FAILURE);
		_manage_the_pipe(data, block_id);
		data->cmds_block[block_id].process_id = fork();
		if (data->cmds_block[block_id].process_id == 0)
		{
			if (block_id <= data->nb_of_pipe)
				close_this(data->cmds_block[block_id].fd_hd[0]);
			duplicate_fds(data, block_id);
			command = add_path_cmd(block_id, data, env);
			execve(command, data->cmds_block[block_id].commands, env);
			perror(command);
			exit(EXIT_FAILURE);
		}
		else if (data->cmds_block[block_id].process_id < 0)
		{
			ft_dprintf(2, RED"Fork Issue: Resource temporarily unavailable\n"END);
			break ;
		}
		if (block_id <= data->nb_of_pipe)
			close_this(data->cmds_block[block_id].fd_hd[1]);
		if (block_id > 0)
			close_this(data->cmds_block[block_id - 1].fd_hd[0]);
		block_id++;
	}
	if (block_id != 0)
		close_this(data->cmds_block[block_id - 1].fd_hd[0]);
	return (SUCCESS);
}

static void	_manage_the_pipe(t_data *data, int block_id)
{
	if (data->cmds_block[block_id].fd_hd[0] == 0)
		return ;
	if (data->cmds_block[block_id].outfile == STDOUT_FILENO)
		data->cmds_block[block_id].outfile = data->cmds_block[block_id].fd_hd[1];
	else
	{
		print_cmd_block("je ferme le fd_ecriture pour \n", data->cmds_block[block_id]);
		close(data->cmds_block[block_id].fd_hd[1]);
	}
	if (data->cmds_block[block_id + 1].infile == STDIN_FILENO)
		data->cmds_block[block_id + 1].infile = data->cmds_block[block_id].fd_hd[0];
	else
		close(data->cmds_block[block_id].fd_hd[0]);

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

static t_return_status _do_the_pipe(t_cmd *cmd_block, int nb_of_pipe, int block_id)
{
	if (block_id == nb_of_pipe)
		return (SUCCESS);
	if (pipe(cmd_block->fd_hd) != 0)
		return (FAILURE);
	return (SUCCESS);
}