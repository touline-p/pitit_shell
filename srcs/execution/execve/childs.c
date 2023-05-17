/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:17:52 by twang             #+#    #+#             */
/*   Updated: 2023/05/16 19:16:54 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/minishell.h"

/*---- prototypes ------------------------------------------------------------*/

static t_return_status	_do_the_pipe(t_cmd *cmd_block, \
									int nb_of_pipe, int block_id);
static void				_manage_the_pipe(t_data *data, int block_id);
void				child_launch_act(t_data *data, \
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
		child_launch_act(data, data->nb_of_pipe, env, block_id);
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

static t_return_status	_is_executable(char *command)
{
	struct stat	st;

	if (stat(command, &st) == 0)
	{
		if (!(st.st_mode & S_IXUSR))
		{
			ft_dprintf(2, "minishell: %s: Permission denied\n", command);
			g_ret_val = 126;
			return (FAILURE);
		}
		if (S_ISDIR(st.st_mode))
		{
			ft_dprintf(2, "minishell: %s: Is a directory\n", command);
			g_ret_val = 126;
			return (FAILURE);
		}
		return (SUCCESS);
	}
	g_ret_val = 127;
	ft_dprintf(2, "minishell: %s: No such file or directory\n", command);
	return (FAILURE);
}



static void _subshell_then_exit(t_cmd command, char ***env)
{
	t_data new_data;

	bzero(&new_data, sizeof(t_data));
	switchman(&new_data, (t_string_token *)command.commands, env);
	ft_free_split(*env);
	exit(g_ret_val);
}

static void _builtin_then_exit(t_cmd command, char ***env)
{
	builtin_switch(command, command.commands, \
						env);
	if (command.id_command == EXPORT)
	{
		free(command.commands[0]);
		free(command.commands);
	}
	else
		ft_free_split(command.commands);
	ft_free_split(*env);
	exit(0);
}

static void _execve_then_exit(t_cmd command, char ***env)
{
	char			*command_str;

	command_str = NULL;
	command_str = add_path_cmd(&command, *env);
	if (command_str != NULL && _is_executable(command_str) == SUCCESS)
	{
		execve(command_str, command.commands, *env);
		perror(command.commands[0]);
		g_ret_val = 127;
	}
	ft_free_split(*env);
	ft_free_split(command.commands);
	exit(g_ret_val);
}

void	child_launch_act(t_data *data, int nb_of_pipe, \
								char ***env, int block_id)
{
	t_cmd			command_block;

	command_block = data->cmds_block[block_id];
	free(data->cmds_block);
	if (block_id <= nb_of_pipe)
		_close_this(command_block.fd_hd[0]);
	if (duplicate_fds(command_block, data, env) != SUCCESS)
	{
		ft_free_split(command_block.commands);
		ft_free_split(*env);
		exit(1);
	}
	if (command_block.id_command == SUBSHELL)
		_subshell_then_exit(command_block, env);
	if (command_block.id_command != CMD && command_block.id_command != EMPTY)
		_builtin_then_exit(command_block, env);
	_execve_then_exit(command_block, env);
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

	if (cmd->id_command == EMPTY || cmd->commands == NULL)
	{
		if (cmd->commands)
		{
			str = ft_strjoin(cmd->commands[0], " : command not found\n");
			g_ret_val = 127;
			write(2, str, ft_strlen(str));
			free(str);
		}
		else
			g_ret_val = 0;
		return (NULL);
	}
	if (is_path(cmd->commands[0]))
		return (cmd->commands[0]);
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

	i = -1;
	while (paths[++i])
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
	}
	g_ret_val = 127;
	ft_free((void **)paths, ft_str_array_len(paths));
	str = ft_strjoin(cmd->commands[0], " : command not found\n");
	if (str == NULL)
		return (NULL);
	write(2, str, ft_strlen(str));
	return (free(str), NULL);
}
