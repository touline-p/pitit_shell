/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:17:52 by twang             #+#    #+#             */
/*   Updated: 2023/05/02 17:36:18 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

/*---- prototypes ------------------------------------------------------------*/

static t_return_status	_do_the_pipe(t_cmd *cmd_block, int nb_of_pipe, int block_id);
static void 			_manage_the_pipe(t_data *data, int block_id);
static void				_close_this(int fd);
static char				*add_path_cmd(int block_id, t_data *data, char **env);

/*----------------------------------------------------------------------------*/

t_return_status	childs_execve(t_data *data, char ***env)
{
	int		block_id;
	char	*command;

	block_id = 0;
	while (block_id < data->nb_of_pipe + 1)
	{
		if (_do_the_pipe(&(data->cmds_block[block_id]), data->nb_of_pipe, block_id) != SUCCESS)
			return (FAILURE);
		_manage_the_pipe(data, block_id);
		signal(SIGINT, SIG_IGN);
		signal(SIGINT, &handle_signal_child);
		data->cmds_block[block_id].process_id = fork();
		/*-----------------------------------------------------------
		if (data->cmds_block[block_id].process_id == -1)
			perror("fork");
		else if (data->cmds_block[block_id].process_id > 0)
		{
			waitpid(data->cmds_block[block_id].process_id, &g_ret_value, 0);
			kill(data->cmds_block[block_id].process_id, SIGTERM);
		}
		--------------------------------------------------------------*/
		if (data->cmds_block[block_id].process_id == 0)
		{
			if (block_id <= data->nb_of_pipe)
				_close_this(data->cmds_block[block_id].fd_hd[0]);
			duplicate_fds(data, block_id);
			if (data->cmds_block[block_id].id_command != CMD)
			{
				exit(builtin_switch(data->cmds_block[block_id].id_command, data->cmds_block[block_id].commands, \
                    env));
			}
			command = add_path_cmd(block_id, data, *env);
			if (command != NULL)
			{
				execve(command, data->cmds_block[block_id].commands, *env);
				perror(data->cmds_block[block_id].commands[0]);
			}
			ft_free_split(data->cmds_block[block_id].commands);
			exit(EXIT_FAILURE);
		}
		else if (data->cmds_block[block_id].process_id < 0)
		{
			ft_free_split(data->cmds_block[block_id].commands);
			ft_dprintf(2, RED"Fork Issue: Resource temporarily unavailable\n"END);
			break ;
		}
		ft_free_split(data->cmds_block[block_id].commands);
		_close_this(data->cmds_block[block_id].infile);
		_close_this(data->cmds_block[block_id].outfile);
		block_id++;
	}
	return (SUCCESS);
}

static t_return_status _do_the_pipe(t_cmd *cmd_block, int nb_of_pipe, int block_id)
{
	if (cmd_block[block_id].infile < 0 || cmd_block[block_id].fd_hd[0] < 0)
		return (FAILURE);
	if (block_id == nb_of_pipe)
		return (SUCCESS);
	if (pipe(cmd_block->fd_hd) != 0)
		return (FAILURE);
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

static void _close_this(int fd)
{
	if (fd > 2)
		close(fd);
}

static char	*add_path_cmd(int block_id, t_data *data, char **env)
{
	int		i;
	char	**paths;
	char 	*ret_val;

	if (is_path(data->cmds_block[block_id].commands[0]))
		return (data->cmds_block[block_id].commands[0]);
	paths = get_paths(env);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		paths[i] = strjoin_path_cmd(paths[i], data->cmds_block[block_id].commands[0]);
		if (paths[i] == NULL)
		{
			ft_free((void **)paths, ft_str_array_len(paths));
			return (NULL);
		}
		if (access(paths[i], X_OK) == 0)
		{
			ret_val = ft_strdup(paths[i]);
			ft_free((void **)paths, ft_str_array_len(paths));
			return (ret_val);
		}
		i++;
	}
	ft_free((void **)paths, ft_str_array_len(paths));
	ft_dprintf(2, "%s : command not found\n", data->cmds_block[block_id].commands[0]);
	return (NULL);
}
