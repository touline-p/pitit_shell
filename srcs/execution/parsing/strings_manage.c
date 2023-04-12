/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_manage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:41:57 by twang             #+#    #+#             */
/*   Updated: 2023/04/12 19:37:46 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

/*---- prototypes ------------------------------------------------------------*/

static t_return_status	alloc_cmds(t_data *data, t_string_token *str_of_tok);
static void				get_raw_cmds(t_data *data, t_string_token *str_of_tok);
static void				set_id_cmds(t_data *data);

/*----------------------------------------------------------------------------*/

void	strings_management(t_data *data, t_string_token *str_of_tok, char **env)
{
	(void)env;
	alloc_cmds(data, str_of_tok);
	get_raw_cmds(data, str_of_tok);
	set_id_cmds(data);
}

static t_return_status	alloc_cmds(t_data *data, t_string_token *str_of_tok)
{
	t_string_token	*temp;
	int				size;
	int				block_id;

	size = 0;
	block_id = 0;
	temp = str_of_tok;
	while (temp != NULL)
	{
		if (temp->token == STRING)
			size++;
		if (temp->token == PIPE)
		{
			data->cmds_block[block_id].commands = \
			ft_calloc((size + 1), sizeof(char *));
			block_id++;
			size = 0;
		}
		temp = temp->next;
	}
	data->cmds_block[block_id].commands = ft_calloc((size + 1), sizeof(char *));
	if (!data->cmds_block[block_id].commands)
		return (FAILED_MALLOC);
	return (SUCCESS);
}

static void	get_raw_cmds(t_data *data, t_string_token *str_of_tok)
{
	int				index;
	int				block_id;
	t_string_token	*temp;

	index = 0;
	block_id = 0;
	temp = str_of_tok;
	while (temp != NULL)
	{
		if (temp->token == STRING)
		{
			data->cmds_block[block_id].commands[index] = \
				ft_strdup(temp->content);
			index++;
		}
		if (temp->token == PIPE)
		{
			block_id++;
			index = 0;
		}
		temp = temp->next;
	}
}

static void	set_id_cmds(t_data *data)
{
	int	block_id;

	block_id = 0;
	while (data && data->cmds_block && data->cmds_block[block_id].commands)
	{
		data->cmds_block[block_id].id_command = \
			is_builtin(data->cmds_block[block_id].commands[0]);
		block_id++;
	}
}

// static t_return_status	add_path_cmd(t_data *data, t_string_token *str_of_tok, char **env)
// {
	
// }
