/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangthea <wangthea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:54:36 by wangthea          #+#    #+#             */
/*   Updated: 2023/04/28 21:47:37 by wangthea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

/*---- prototypes ------------------------------------------------------------*/

static t_return_status	alloc_cmd_block(t_data *data, \
t_string_token *lst_of_tok);
static t_return_status	check_if_token(t_string_token *lst_of_tok);
static void				wait_for_process_ids(t_data *data);

/*----------------------------------------------------------------------------*/

void	execution(t_data *data, t_string_token *lst_of_tok, char ***env_pt)
{
	ft_bzero(data, sizeof(t_data));
	alloc_cmd_block(data, lst_of_tok);
	infiles_management(data, lst_of_tok, *env_pt);
	outfiles_management(data, lst_of_tok, *env_pt);
	clean_files_token(lst_of_tok);
	clean_token(lst_of_tok);
	if (check_if_token(lst_of_tok) != SUCCESS)
		return ;
	strings_management(data, lst_of_tok, *env_pt);
	if (data->nb_of_pipe == 0 && data->cmds_block->id_command != CMD)
		switchman_once(data, env_pt);
	else
		childs_execve(data, env_pt);
	wait_for_process_ids(data);
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
	data->cmds_block = (t_cmd *)ft_calloc((data->nb_of_pipe + 2), sizeof(t_cmd));
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

static void	wait_for_process_ids(t_data *data)
{
	int	block_id;

	block_id = 0;
	while (block_id < data->nb_of_pipe + 1)
	{
		waitpid(data->cmds_block[block_id].process_id, &g_ret_val, 0);
		if (block_id == data->nb_of_pipe)
		{
			g_ret_val = WEXITSTATUS(g_ret_val);
			break;
		}
		block_id++;
	}
}
/* ---- test it like it's hot ------------

static void	wait_for_process_ids(t_data *data)
{
	int		block_id;
	int		status;
	bool	have_signal;

	block_id = 0;
	status = 0;
	have_signal = false;
	while (block_id < data->nb_of_pipe + 1)
	{
		if (waitpid(data->cmds_block[block_id].process_id, &status, WUNTRACED) == -1)
		{
			ft_dprintf(2, RED"minishell: waitpid: process %d failed\n"END, block_id);
			break ;
		}
		else if (WIFEXITED(status))
			g_ret_val = WEXITSTATUS(status);
		else if (WIFSIGNALED(status) && have_signal == false)
		{
			handle_signal_child(WTERMSIG(status));
			have_signal = true;
		}
		block_id++;
	}

}
----------------------------------------- */
