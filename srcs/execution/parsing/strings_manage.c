/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_manage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:41:57 by twang             #+#    #+#             */
/*   Updated: 2023/05/12 14:46:06 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

/*---- prototypes ------------------------------------------------------------*/

static t_return_status	get_raw_cmds(t_data *data, t_string_token *lst_of_tok, char **env);
static void				set_id_cmds(t_data *data);

/*----------------------------------------------------------------------------*/

void	strings_management(t_data *data, t_string_token *lst_of_tok, char **env)
{
	get_raw_cmds(data, lst_of_tok, env);
	set_id_cmds(data);
}


static t_return_status	get_raw_cmds(t_data *data, t_string_token *lst_of_tok, char **env)
{
	t_string_token	*temp;
	int				block_id;

	block_id = 0;
	temp = lst_of_tok;
	while (temp->token != EOL)
	{
		data->cmds_block[block_id].commands = join_token_lst(&temp, env);
		expand_wildcards(&(data->cmds_block[block_id].commands));
		block_id++;
	}
	data->cmds_block[block_id].commands = NULL;
	
	if (!data->cmds_block[block_id].commands)
		return (FAILED_MALLOC);
	return (SUCCESS);
}

static void	set_id_cmds(t_data *data)
{
	int	block_id;

	block_id = 0;
	while (data->cmds_block[block_id].commands)
	{
		data->cmds_block[block_id].id_command =
			is_builtin(data->cmds_block[block_id].commands[0]);
		block_id++;
	}
}
