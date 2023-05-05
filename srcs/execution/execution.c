/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:54:36 by wangthea          #+#    #+#             */
/*   Updated: 2023/05/05 17:08:45 by twang            ###   ########.fr       */
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
	if (g_ret_val == 130)
		return ;
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
	int		block_id;
	int		status;

	block_id = 0;
	status = 0;
	while (block_id < data->nb_of_pipe + 1)
	{
		if (data->cmds_block[block_id].id_command == CMD)
		{
			if (waitpid(data->cmds_block[block_id].process_id, &status, WUNTRACED) == -1)
			{
				g_ret_val = 1;
				break ;
			}
			if (WIFEXITED(status))
				g_ret_val = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				g_ret_val = WTERMSIG(status);
				if (g_ret_val != 131)
					g_ret_val += 128;
			}
		}
		block_id++;
	}
}
