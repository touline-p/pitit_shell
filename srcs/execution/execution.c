/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:54:36 by wangthea          #+#    #+#             */
/*   Updated: 2023/04/19 16:48:49 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

/*---- prototypes ------------------------------------------------------------*/

static t_return_status	alloc_cmd_block(t_data *data, \
t_string_token *lst_of_tok);
static void				wait_for_process_ids(t_data *data);

/*----------------------------------------------------------------------------*/

void	execution(t_string_token *lst_of_tok, char ***env_pt)
{
	t_data	data;

	display_str_token(lst_of_tok);
	ft_bzero(&data, sizeof(t_data));
	alloc_cmd_block(&data, lst_of_tok);
	infiles_management(&data, lst_of_tok, *env_pt);
	outfiles_management(&data, lst_of_tok);
//	if (expand_for_args(lst_of_tok, *env_pt) != SUCCESS)
//		return ;
	clean_files_token(lst_of_tok);
	clean_token(lst_of_tok);
	strings_management(&data, lst_of_tok, *env_pt);
	string_token_destructor(lst_of_tok);
	print_cmd_block("bonjour" , data.cmds_block[0]);
	return ;
	builtin_switch(data.cmds_block->id_command, data.cmds_block->commands, \
					env_pt);
	childs_execve(&data, *env_pt);
	wait_for_process_ids(&data);
	if (data.cmds_block->commands)
		free_commands(&data);
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

static void	wait_for_process_ids(t_data *data)
{
	int	block_id;
	int	status;

	block_id = 0;
	status = 0;
	while (block_id < data->nb_of_pipe + 1)
	{
		waitpid(data->cmds_block[block_id].process_id, &status, 0);
		if (WEXITSTATUS(status) && block_id == data->nb_of_pipe)
			exit(127);
		block_id++;
	}
}
