/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infiles_manage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:01:03 by twang             #+#    #+#             */
/*   Updated: 2023/05/15 09:44:49 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"
#include "../../incs/parsing_incs/minishell_parsing.h"

/*---- prototypes ------------------------------------------------------------*/

static t_return_status	_set_infile(t_data *data, char **file, int block_id, char **env);
static t_return_status	_set_heredoc(t_data *data, char *hr_doc, int block_id);

/*----------------------------------------------------------------------------*/

bool	is_err_next_to_pipe(t_emt token)
{
	if (token > CHEVRON_OT && token != STRING)
		return (false);
	return (true);
}

static t_return_status	_set_outfile(t_data *data, char **file, \
									int block_id, char **env)
{
	char	**arr;
	bool	signal;

	signal = file_is_empty(*file);
	check_opened_outfiles(data, block_id);
	if (data->cmds_block[block_id].infile < 0
		|| data->cmds_block[block_id].outfile < 0
		|| data->cmds_block[block_id].fd_hd[0] < 0
		|| data->cmds_block[block_id].is_ambiguous == true)
		return (SUCCESS);
	cut_line_on(*file, &arr);
	join_arr_on(arr, file, env);
	if (wildcard_files(data, file, block_id) != SUCCESS)
		return (SUCCESS);
	if (ft_strchr(*file, -32) != NULL || (**file == 0 && signal))
	{
		manage_ambiguous(&(data->cmds_block[block_id]), *file);
		return (SUCCESS);
	}
	data->cmds_block[block_id].outfile = open(*file, O_WRONLY | O_CREAT | \
	O_TRUNC, 0644);
	if (data->cmds_block[block_id].outfile == -1)
	{
		g_ret_val = 1;
		perror(*file);
		return (FAILURE);
	}
	return (SUCCESS);
}

static t_return_status	_set_appends(t_data *data, char **file, \
									int block_id, char **env)
{
	char	**arr;
	bool	signal;

	signal = file_is_empty(*file);
	check_opened_outfiles(data, block_id);
	if (data->cmds_block[block_id].infile < 0
		|| data->cmds_block[block_id].outfile < 0
		|| data->cmds_block[block_id].fd_hd[0] < 0
		|| data->cmds_block[block_id].is_ambiguous == true)
		return (SUCCESS);
	cut_line_on(*file, &arr);
	join_arr_on(arr, file, env);
	if (wildcard_files(data, file, block_id) != SUCCESS)
		return (SUCCESS);
	if (ft_strchr(*file, -32) != NULL || (**file == 0 && signal))
	{
		manage_ambiguous(&(data->cmds_block[block_id]), *file);
		return (SUCCESS);
	}
	data->cmds_block[block_id].outfile = open(*file, O_WRONLY | O_CREAT | \
	O_APPEND, 0644);
	if (data->cmds_block[block_id].outfile == -1)
	{
		g_ret_val = 1;
		perror(*file);
		return (FAILURE);
	}
	return (SUCCESS);
}

t_return_status	infiles_management(t_data *data, t_string_token *lst_of_tok, char **env)
{
	int				i;
	t_string_token	*temp;

	i = 0;
	temp = lst_of_tok;
	while (temp != NULL)
	{
		if (temp->token == CHEVRON_IN)
		{
			temp = temp->next;
			_set_infile(data, &(temp->content), i, env);
		}
		else if (temp->token == HERE_DOC)
		{
			temp = temp->next;
			_set_heredoc(data, temp->content, i);
			temp->content = NULL;
		}
		else if (temp->token == CHEVRON_OT)
		{
			temp = temp->next;
			_set_outfile(data, &(temp->content), i, env);
		}
		else if (temp->token == APPENDS)
		{
			temp = temp->next;
			_set_appends(data, &(temp->content), i, env);
		}
		else if (temp->token == PIPE)
			i++;
		if (temp->token == O_PRTSS)
		{
			data->cmds_block[i].id_command = SUBSHELL;
			go_to_next_(C_PRTSS, temp->next, &temp);
		}
		else
			temp = temp->next;
	}
	return (SUCCESS);
}

static t_return_status	_set_infile(t_data *data, char **file, int block_id, char **env)
{
	char	**arr;
	bool	signal;

	check_opened_infiles(data, block_id);
	signal = file_is_empty(*file);
	if (data->cmds_block[block_id].infile < 0
		|| data->cmds_block[block_id].outfile < 0
		|| data->cmds_block[block_id].fd_hd[0] < 0
		|| data->cmds_block[block_id].is_ambiguous == true)
		return (SUCCESS);
	cut_line_on(*file, &arr);
	join_arr_on(arr, file, env);
	if (wildcard_files(data, file, block_id) != SUCCESS)
		return (SUCCESS);
	if (ft_strchr(*file, -32) != NULL || (**file == 0 && signal))
	{
		manage_ambiguous(&(data->cmds_block[block_id]), *file);
		return (FAILURE);
	}
	data->cmds_block[block_id].infile = open(*file, O_RDONLY, 0644);
	if (data->cmds_block[block_id].is_heredoc == true)
	{
		free(data->cmds_block[block_id].heredoc_data);
		data->cmds_block[block_id].is_heredoc = false;
	}
	if (data->cmds_block[block_id].infile == -1)
	{
		g_ret_val = 1;
		perror(*file);
		return (FAILURE);
	}
	return (SUCCESS);
}

static t_return_status	_set_heredoc(t_data *data, char *hr_data, int block_id)
{
	check_opened_infiles(data, block_id);
	if (data->cmds_block[block_id].infile < 0
		|| data->cmds_block[block_id].outfile < 0
		|| data->cmds_block[block_id].fd_hd[0] < 0
		|| data->cmds_block[block_id].is_ambiguous == true)
		return (SUCCESS);
	if (data->cmds_block[block_id].is_heredoc)
		free(data->cmds_block[block_id].heredoc_data);
	data->cmds_block[block_id].is_heredoc = true;
	data->cmds_block[block_id].heredoc_data = hr_data;
	return (SUCCESS);
}


