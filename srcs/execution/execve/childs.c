/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:17:52 by twang             #+#    #+#             */
/*   Updated: 2023/05/05 17:17:11 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

/*---- prototypes ------------------------------------------------------------*/

static t_return_status	_do_the_pipe(t_cmd *cmd_block, int nb_of_pipe, int block_id);
static void 			_manage_the_pipe(t_data *data, int block_id);
static void				_child_launch_act(t_cmd *command_block, int nb_of_pipe, char ***env, int block_id);
static char				*add_path_cmd(t_cmd *cmd, char **env);
static void				_close_this(int fd);

/*----------------------------------------------------------------------------*/

void free_all_others(t_cmd *cmds, int block_id, int nb_of_pipes)
{
	int i;

	i = 0;
	while (i < nb_of_pipes + 1)
	{
		if (i != block_id)
			ft_free_split(cmds[block_id].commands);
		i++;
	}
	(void)cmds; (void)block_id; (void)(nb_of_pipes);
	return ;
}

t_return_status	childs_execve(t_data *data, char ***env)
{
	int		block_id;

	block_id = 0;
	while (block_id < data->nb_of_pipe + 1)
	{
		print_cmd_block(ft_itoa(block_id), data->cmds_block[block_id]);
		if (_do_the_pipe(&(data->cmds_block[block_id]), data->nb_of_pipe, block_id) != SUCCESS)
			return (FAILURE);
		_manage_the_pipe(data, block_id);
		signal(SIGINT, &handle_signal_child);
		signal(SIGQUIT, &handle_signal_child);
		data->cmds_block[block_id].process_id = fork();
		if (data->cmds_block[block_id].process_id == -1)
			perror("fork");
		if (data->cmds_block[block_id].process_id == 0)
		{
			free(data->prompt);
			//free_all_others(data->cmds_block, block_id, data->nb_of_pipe);
			_child_launch_act(&(data->cmds_block[block_id]), data->nb_of_pipe, env, block_id);
		}
		else if (data->cmds_block[block_id].process_id < 0)
		{
			ft_free_split(data->cmds_block[block_id].commands);
			ft_dprintf(2, RED"minishell: fork: ressource temporarily unavailable\n"END);
			break ;
		}
		ft_free_split(data->cmds_block[block_id].commands);
		_close_this(data->cmds_block[block_id].infile);
		_close_this(data->cmds_block[block_id].outfile);
		block_id++;
	}
	return (SUCCESS);
}

static void	_child_launch_act(t_cmd *command_block, int nb_of_pipe, char ***env, int block_id)
{
	char *command;
	
	command = NULL;
	if (block_id <= nb_of_pipe)
		_close_this(command_block->fd_hd[0]);
	if (duplicate_fds(*command_block) != SUCCESS)
	{
		ft_free_split(command_block->commands);
		exit(1);
	}
	if (command_block->id_command != CMD)
	{
		exit(builtin_switch(command_block->id_command, command_block->commands, \
			env));
	}
	command = add_path_cmd(command_block, *env);
	if (command != NULL)
	{
		execve(command, command_block->commands, *env);
		perror(command_block->commands[0]);
	}
	ft_free_split(command_block->commands);
	g_ret_val = 127;
	exit(g_ret_val);
}

static t_return_status	_do_the_pipe(t_cmd *cmd_block, int nb_of_pipe, int block_id)
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
		close(data->cmds_block[block_id].fd_hd[1]);
	if (data->cmds_block[block_id + 1].infile == STDIN_FILENO)
		data->cmds_block[block_id + 1].infile = data->cmds_block[block_id].fd_hd[0];
	else
		close(data->cmds_block[block_id].fd_hd[0]);

}

static void	_close_this(int fd)
{
	if (fd > 2)
		close(fd);
}

static char	*add_path_cmd(t_cmd *cmd, char **env)
{
	int		i;
	char	**paths;
	char 	*ret_val;

	if (is_path(cmd->commands[0]))
		return (cmd->commands[0]);
	paths = get_paths(env);
	if (!paths)
		return (NULL);
	i = 0;
	if (ft_strcmp("", cmd->commands[0]) == 0)
	{
		ft_dprintf(2, "%s : command not found\n", cmd->commands[0]);
		return (ft_free_split(paths), NULL);
	}
	while (paths[i])
	{
		paths[i] = strjoin_path_cmd(paths[i], cmd->commands[0]);
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
	ft_dprintf(2, "%s : command not found\n", cmd->commands[0]);
	return (NULL);
}
