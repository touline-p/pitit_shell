/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:54:36 by wangthea          #+#    #+#             */
/*   Updated: 2023/05/10 17:39:58 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

/*---- prototypes ------------------------------------------------------------*/

static t_return_status	alloc_cmd_block(t_data *data, \
t_string_token *lst_of_tok);
static t_return_status	check_if_token(t_string_token *lst_of_tok);
static void				wait_for_process_ids(t_data *data);

/*----------------------------------------------------------------------------*/

bool	check_cmd(t_cmd *cmd)
{
	while (cmd->commands)
	{
		if (cmd->infile == -1 && cmd->is_heredoc == true)
			return (true);
		cmd++;
	}
	return (false);
}

void	init_data(t_data *data)
{
	data->cmds_block = NULL;
	data->fd[0] = 0;
	data->fd[1] = 0;
	data->nb_of_pipe = 0;
}

t_return_status	fix_string(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_pipe + 1)
	{
		if (data->cmds_block[i].id_command != SUBSHELL && data->cmds_block[i].commands[0] == NULL)
		{
			free(data->cmds_block[i].commands);
			data->cmds_block[i].commands = malloc(sizeof(char *) * 2);
			if (data->cmds_block[i].commands == NULL)
				return (FAILED_MALLOC);
			data->cmds_block[i].commands[0] = ft_strdup("");
			if (data->cmds_block[i].commands[0] == NULL)
			{
				data->cmds_block[i].commands = NULL;
				return (free(data->cmds_block[i].commands), FAILED_MALLOC);
			}
			data->cmds_block[i].commands[1] = NULL;
		}
		i++;
	}
	return (SUCCESS);
}

void	execution(t_data *data, t_string_token *lst_of_tok, char ***env_pt)
{
	init_data(data);
	alloc_cmd_block(data, lst_of_tok);
	infiles_management(data, lst_of_tok, *env_pt);
	outfiles_management(data, lst_of_tok, *env_pt);
	clean_files_token(lst_of_tok);
	clean_token(lst_of_tok);
	if (check_if_token(lst_of_tok) != SUCCESS)
	{
		string_token_destructor(lst_of_tok);
		return ;
	}
	strings_management(data, lst_of_tok, *env_pt);
	fix_string(data);
	string_token_destructor(lst_of_tok);
	if (g_ret_val == 130 && check_cmd(data->cmds_block))
		return ;
	if (data->nb_of_pipe == 0 && data->cmds_block->id_command != CMD && data->cmds_block->id_command != SUBSHELL)
		switchman_once(data, env_pt);
	else
	{
		childs_execve(data, env_pt);
		wait_for_process_ids(data);
	}
	free(data->cmds_block);
}

static t_return_status	alloc_cmd_block(t_data *data, \
									t_string_token *lst_of_tok)
{
	t_string_token	*temp;
	int				i;

	temp = lst_of_tok;
	while (temp != NULL)
	{
		if (temp->token == PIPE)
			data->nb_of_pipe++;
		temp = temp->next;
	}
	data->cmds_block = ft_calloc((data->nb_of_pipe + 2), sizeof(t_cmd));
	if (!data->cmds_block)
		return (FAILED_MALLOC);
	i = 0;
	while (i < data->nb_of_pipe + 1)
		data->cmds_block[i++].outfile = 1;
	return (SUCCESS);
}

static t_return_status	check_if_token(t_string_token *lst_of_tok)
{
	t_string_token	*temp;

	temp = lst_of_tok;
	while (temp != NULL)
	{
		if (temp->token != START && temp->token != EOL)
			return (SUCCESS);
		temp = temp->next;
	}
	return (FAILURE);
}

t_return_status	wait_for_command(int pid, int *status, bool *signals)
{
	if (waitpid(pid, status, WUNTRACED) == -1)
	{
		g_ret_val = 1;
		return (false);
	}
	else if (WIFEXITED(*status))
		g_ret_val = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status) && *signals == false)
	{
		handle_signal_child(WTERMSIG(*status));
		*signals = true;
	}
	return (true);
}

static void	wait_for_process_ids(t_data *data)
{
	int		block_id;
	int		status;
	bool	signals;

	block_id = 0;
	status = 0;
	signals = false;
	while (block_id < data->nb_of_pipe + 1)
	{
		if (wait_for_command(data->cmds_block[block_id].process_id, \
								&status, &signals) == false)
			break;
		block_id++;
	}
}
