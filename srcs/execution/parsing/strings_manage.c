/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_manage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:41:57 by twang             #+#    #+#             */
/*   Updated: 2023/04/14 15:41:57 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

/*---- prototypes ------------------------------------------------------------*/

static t_return_status	alloc_cmds(t_data *data, t_string_token *lst_of_tok);
static void				get_raw_cmds(t_data *data, t_string_token *lst_of_tok);
static void				set_id_cmds(t_data *data);
// static t_return_status	add_path_cmd(int block_id, t_data *data, char **env);

/*----------------------------------------------------------------------------*/

void	strings_management(t_data *data, t_string_token *lst_of_tok, char **env)
{
	(void)env;
	alloc_cmds(data, lst_of_tok);
	get_raw_cmds(data, lst_of_tok);
	set_id_cmds(data);
	/* ---- to put inside execution loop ------
	if (data->cmds_block[0].id_command == CMD)
		add_path_cmd(0, data, env);
	-------------------------------------------*/
}

static t_return_status	alloc_cmds(t_data *data, t_string_token *lst_of_tok)
{
	t_string_token	*temp;
	int				size;
	int				block_id;

	size = 0;
	block_id = 0;
	temp = lst_of_tok;
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

static void	get_raw_cmds(t_data *data, t_string_token *lst_of_tok)
{
	int				index;
	int				block_id;
	t_string_token	*temp;

	index = 0;
	block_id = 0;
	temp = lst_of_tok;
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
	while (data->cmds_block[block_id].commands)
	{
		data->cmds_block[block_id].id_command = \
			is_builtin(data->cmds_block[block_id].commands[0]);
		block_id++;
	}
}

/*
static t_return_status	add_path_cmd(int block_id, t_data *data, char **env)
{
	int		i;
	char	**paths;

	if (access(data->cmds_block[block_id].commands[0], X_OK) == 0)
		return (SUCCESS);
	paths = get_paths(env);
	if (!paths)
		return (FAILED_MALLOC);
	i = 0;
	while (paths[i])
	{
		paths[i] = strjoin_path_cmd(paths[i], data->cmds_block[block_id].commands[0]);
		if (!paths[i])
		{
			ft_free((void **)paths, get_path_size(paths));
			return (FAILED_MALLOC);
		}
		if (access(paths[i], X_OK) == 0)
		{
			printf(BLUE"command without paths? %s\n"END, data->cmds_block[block_id].commands[0]);
			data->cmds_block[block_id].commands[0] = ft_strdup(paths[i]);
			printf(BLUE"command with paths? %s\n"END, data->cmds_block[block_id].commands[0]);
			ft_free((void **)paths, get_path_size(paths));
			return (SUCCESS);
		}
		i++;
	}
	return (FAILURE);
}
*/