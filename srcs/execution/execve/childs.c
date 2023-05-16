/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:17:52 by twang             #+#    #+#             */
/*   Updated: 2023/05/16 11:44:13 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

/*---- prototypes ------------------------------------------------------------*/

static t_return_status	_do_the_pipe(t_cmd *cmd_block, \
									int nb_of_pipe, int block_id);
static void				_manage_the_pipe(t_data *data, int block_id);
static void				_child_launch_act(t_data *data, \
						int nb_of_pipe, char ***env, int block_id);
static char				*add_path_cmd(t_cmd *cmd, char **env);
static void				_close_this(int fd);
static char				*_get_cmd_from_path(t_cmd *cmd, char **paths);

/*----------------------------------------------------------------------------*/

void	free_all_others(t_cmd *cmds, int block_id, int nb_of_pipes)
{
	while (block_id++ < nb_of_pipes + 1)
		ft_free_split(cmds[block_id].commands);
}

static t_return_status	_fork_process(t_data *data, int pid, \
									int block_id, char ***env)
{
	if (pid == 0)
	{
		signal(SIGINT, &handle_signal_child);
		signal(SIGQUIT, &handle_signal_child);
		ft_free_all_str_lst(data, data->index);
		free(data->prompt);
		free_all_others(data->cmds_block, block_id, data->nb_of_pipe);
		_child_launch_act(data, data->nb_of_pipe, env, block_id);
	}
	else if (pid < 0)
	{
		perror("fork");
		ft_free_split(data->cmds_block[block_id].commands);
		free(data->cmds_block[block_id].heredoc_data);
		ft_dprintf(2, \
			RED"minishell: fork: ressource temporarily unavailable\n"END);
		return (FAILURE);
	}
	return (SUCCESS);
}

t_return_status	childs_execve(t_data *data, char ***env)
{
	int		block_id;

	block_id = 0;
	while (block_id < data->nb_of_pipe + 1)
	{
		if (_do_the_pipe(&(data->cmds_block[block_id]), \
						data->nb_of_pipe, block_id) != SUCCESS)
			return (FAILURE);
		_manage_the_pipe(data, block_id);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		data->cmds_block[block_id].process_id = fork();
		_fork_process(data, data->cmds_block[block_id].process_id, \
						block_id, env);
		if (data->cmds_block[block_id].id_command == SUBSHELL)
			string_token_destructor((t_string_token *)data->cmds_block[block_id].commands);
		else
			ft_free_split(data->cmds_block[block_id].commands);
		free(data->cmds_block[block_id].heredoc_data);
		_close_this(data->cmds_block[block_id].infile);
		_close_this(data->cmds_block[block_id].outfile);
		block_id++;
	}
	return (SUCCESS);
}

static t_return_status _is_executable(char *command)
{
	struct stat	st;

	if (stat(command, &st) == 0)
	{
		if (!(st.st_mode & S_IXUSR))
		{
			ft_dprintf(2,"minishell: %s: Permission denied\n", command);
			g_ret_val = 126;
			return (FAILURE);
		}
		if (S_ISDIR(st.st_mode))
		{
			ft_dprintf(2,"minishell: %s: Is a directory\n", command);
			g_ret_val = 126;
			return (FAILURE);
		}
		return (SUCCESS);
	}
	g_ret_val = 126;
	ft_dprintf(2,"minishell: %s: Permission denied\n", command);
	return (SUCCESS);
}

static void	_child_launch_act(t_data *data, int nb_of_pipe, \
								char ***env, int block_id)
{
	char	*command;
	t_cmd	*command_block;
	t_data	new_data;

	bzero(&new_data, sizeof(t_data));
	command_block = &(data->cmds_block[block_id]);
	command = NULL;
	if (block_id <= nb_of_pipe)
		_close_this(command_block->fd_hd[0]);
	if (duplicate_fds(*command_block, data, env) != SUCCESS)
	{
		ft_free_split(command_block->commands);
		exit(1);
	}
	if (command_block->id_command == SUBSHELL)
	{
		switchman(&new_data, (t_string_token *) command_block->commands, env);
		exit(g_ret_val);
	}
	if (command_block->id_command != CMD)
		exit(builtin_switch(command_block->id_command, command_block->commands, \
			env));
	command = add_path_cmd(command_block, *env);
	if (command != NULL && _is_executable(command) == SUCCESS)
	{
		execve(command, command_block->commands, *env);
		perror(command_block->commands[0]);
		g_ret_val = 127;
	}
	ft_free_split(*env);
	ft_free_split(command_block->commands);
	free(data->cmds_block);
	exit(g_ret_val);
}

static t_return_status	_do_the_pipe(t_cmd *cmd_block, \
						int nb_of_pipe, int block_id)
{
	if (block_id == nb_of_pipe)
		return (SUCCESS);
	if (pipe(cmd_block->fd_hd) != 0)
		return (FAILURE);
	return (SUCCESS);
}

static void	_manage_the_pipe(t_data *data, int block_id)
{
	t_cmd	*cmd;

	cmd = &(data->cmds_block[block_id]);
	if (cmd->fd_hd[0] == 0)
		return ;
	if (cmd->outfile == STDOUT_FILENO)
		cmd->outfile = cmd->fd_hd[1];
	else
		close(cmd->fd_hd[1]);
	if ((cmd + 1)->infile == STDIN_FILENO)
		(cmd + 1)->infile = cmd->fd_hd[0];
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
	char	**paths;
	char	*str;

	if (is_path(cmd->commands[0]))
		return (cmd->commands[0]);
	if (ft_strcmp("", cmd->commands[0]) == 0)
	{
		if (cmd->id_command != EMPTY)
			return (NULL);
		str = ft_strjoin(cmd->commands[0], " : command not found\n");
		g_ret_val = 127;
		write(2, str, ft_strlen(str));
		free(str);
		return (NULL);
	}
	paths = get_paths(env);
	str = NULL;
	if (!paths)
		return (NULL);
	return (_get_cmd_from_path(cmd, paths));
}

static char	*_get_cmd_from_path(t_cmd *cmd, char **paths)
{
	int		i;
	char	*str;
	char	*ret_val;

	i = 0;
	str = NULL;
	ret_val = NULL;
	while (paths[i])
	{
		paths[i] = strjoin_path_cmd(paths[i], cmd->commands[0]);
		if (paths[i] == NULL)
			return (ft_free((void **)paths, ft_str_array_len(paths)), NULL);
		if (access(paths[i], X_OK) == 0)
		{
			ret_val = ft_strdup(paths[i]);
			ft_free((void **)paths, ft_str_array_len(paths));
			return (ret_val);
		}
		i++;
	}
	g_ret_val = 127;
	ft_free((void **)paths, ft_str_array_len(paths));
	str = ft_strjoin(cmd->commands[0], " : command not found\n");
	if (str == NULL)
		return (NULL);
	write(2, str, ft_strlen(str));
	free(str);
	return (NULL);
}
