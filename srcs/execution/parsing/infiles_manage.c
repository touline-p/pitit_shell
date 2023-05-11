/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infiles_manage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:01:03 by twang             #+#    #+#             */
/*   Updated: 2023/05/05 17:17:40 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"
#include "../../incs/parsing_incs/minishell_parsing.h"

/*---- prototypes ------------------------------------------------------------*/

static t_return_status	_set_infile(t_data *data, char **file, int block_id, char **env);
static t_return_status	_set_heredoc(t_data *data, char *hr_doc, int block_id);

/*----------------------------------------------------------------------------*/
//// to do check le here doc pour qu'il fonctionne (c'est mieux) recuperer le hr data et set les variables
bool	is_err_next_to_pipe(t_emt token)
{
	if (token > CHEVRON_OT && token != STRING)
		return (false);
	return (true);
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
			if (_set_infile(data, &(temp->content), i, env) == FAILURE)
				go_to_next_(PIPE, temp, &temp);
		}
		if (temp->token == HERE_DOC)
		{
			temp = temp->next;
			_set_heredoc(data, temp->content, i);
			temp->content = NULL;
		}
		if (temp->token == PIPE)
			i++;
		temp = temp->next;
		if (temp->token == O_PRTSS)
			go_to_next_(C_PRTSS, temp, &temp);
	}
	return (SUCCESS);
}


static t_return_status	_set_infile(t_data *data, char **file, int block_id, char **env)
{
	char	**arr;
	bool	signal;

	check_opened_infiles(data, block_id);
	signal = file_is_empty(*file);
	cut_line_on(*file, &arr);
	join_arr_on(arr, file, env);
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
		perror(*file);
		return (FAILURE);
	}
	return (SUCCESS);
}

static t_return_status	_set_heredoc(t_data *data, char *hr_data, int block_id)
{
	check_opened_infiles(data, block_id);
	if (data->cmds_block[block_id].is_heredoc)
		free(data->cmds_block[block_id].heredoc_data);
	data->cmds_block[block_id].is_heredoc = true;
	data->cmds_block[block_id].heredoc_data = hr_data;
	return (SUCCESS);
}


