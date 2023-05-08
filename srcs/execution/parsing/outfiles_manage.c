/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfiles_manage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:01:03 by twang             #+#    #+#             */
/*   Updated: 2023/05/05 15:13:39 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"
#include "../../incs/parsing_incs/minishell_parsing.h"

/*---- prototypes ------------------------------------------------------------*/

static t_return_status	_set_outfile(t_data *data, char **file, int block_id, char **env);
static t_return_status	_set_appends(t_data *data, char **file, int block_id, char **env);

/*----------------------------------------------------------------------------*/

void	false_space_to_space(char *str)
{
	while (*str)
	{
		if (*str == -32)
			*str = 32;
		str++;
	}
}

void	manage_ambiguous(t_cmd *cmd, char *file)
{
	cmd->outfile = -1;
	cmd->is_ambiguous = true;
	false_space_to_space(file);
	ft_dprintf(2, "minishell: %s: ambiguous redirect\n", file);
}

t_return_status	outfiles_management(t_data *data, t_string_token *lst_of_tok, char **env)
{
	int					i;
	t_string_token		*temp;

	i = 0;
	temp = lst_of_tok;
	while (temp != NULL)
	{
		if (temp->token == CHEVRON_OT)
		{
			temp = temp->next;
			if (_set_outfile(data, &(temp->content), i, env) == FAILURE)
				return (FAILURE);
		}
		if (temp->token == APPENDS)
		{
			temp = temp->next;
			if (_set_appends(data, &(temp->content), i, env) == FAILURE)
				return (FAILURE);
		}
		if (temp->token == PIPE)
		{
			i++;
		}
		temp = temp->next;
	}
	return (SUCCESS);
}

static t_return_status	_set_outfile(t_data *data, char **file, int block_id, char **env)
{
	char **arr;
	bool	signal;

	signal = file_is_empty(*file);
	check_opened_outfiles(data, block_id);
	if (data->cmds_block[block_id].infile < 0 || data->cmds_block[block_id].fd_hd[0] < 0
		|| data->cmds_block[block_id].is_ambiguous == true)
		return (SUCCESS);
	cut_line_on(*file, &arr);
	join_arr_on(arr, file, env);
	if (ft_strchr(*file, -32) != NULL || (**file == 0 && signal))
	{
		manage_ambiguous(&(data->cmds_block[block_id]), *file);
		return (SUCCESS);
	}
	data->cmds_block[block_id].outfile = open(*file, O_WRONLY | O_CREAT | \
	O_TRUNC, 0644);
	if (data->cmds_block[block_id].outfile == -1)
	{
		perror(*file);
		return (FAILURE);
	}
	return (SUCCESS);
}

static t_return_status	_set_appends(t_data *data, char **file, int block_id, char **env)
{	
	char **arr;
	bool	signal;

	signal = file_is_empty(*file);
	check_opened_outfiles(data, block_id);
	if (data->cmds_block[block_id].infile < 0 || data->cmds_block[block_id].fd_hd[0] < 0
		|| data->cmds_block[block_id].is_ambiguous == true)
		return (SUCCESS);
	cut_line_on(*file, &arr);
	join_arr_on(arr, file, env);
	
	if (ft_strchr(*file, -32) != NULL || (**file == 0 && signal))
	{
		manage_ambiguous(&(data->cmds_block[block_id]), *file);
		return (SUCCESS);
	}
	data->cmds_block[block_id].outfile = open(*file, O_WRONLY | O_CREAT | \
	O_APPEND, 0644);
	if (data->cmds_block[block_id].outfile == -1)
	{
		perror(*file);
		return (FAILURE);
	}
	return (SUCCESS);
}
