/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_manage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:41:57 by twang             #+#    #+#             */
/*   Updated: 2023/04/17 18:26:34 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

/*---- prototypes ------------------------------------------------------------*/

static t_return_status	get_raw_cmds(t_data *data, t_string_token *lst_of_tok);
static void				set_id_cmds(t_data *data);
/*static t_return_status	add_path_cmd(int block_id, t_data *data, char **env);*/

/*----------------------------------------------------------------------------*/

void	strings_management(t_data *data, t_string_token *lst_of_tok, char **env)
{
	(void)env;
	get_raw_cmds(data, lst_of_tok);
	int i = 0;
	while (i <= data->nb_of_pipe)
		ft_print_split(data->cmds_block[i++].commands);
	set_id_cmds(data);
	/* ---- to put inside execution loop ------  
	if (data->cmds_block[0].id_command == CMD)
		add_path_cmd(0, data, env);*/
}
char **join_token_lst(t_string_token **arg);

static t_return_status	get_raw_cmds(t_data *data, t_string_token *lst_of_tok)
{
	t_string_token	*temp;
	int				block_id;

	block_id = 0;
	temp = lst_of_tok;
	while (temp->token != EOL)
		data->cmds_block[block_id++].commands = join_token_lst(&temp);
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