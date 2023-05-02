/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfiles_manage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:01:03 by twang             #+#    #+#             */
/*   Updated: 2023/05/02 16:24:55 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"
#include "../../incs/parsing_incs/minishell_parsing.h"

/*---- prototypes ------------------------------------------------------------*/

static void	set_outfile(t_data *data, char **file, int block_id, char **env);
static void	set_appends(t_data *data, char **file, int block_id, char **env);

/*----------------------------------------------------------------------------*/

void	outfiles_management(t_data *data, t_string_token *lst_of_tok, char **env)
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
			set_outfile(data, &(temp->content), i, env);
		}
		if (temp->token == APPENDS)
		{
			temp = temp->next;
			set_appends(data, &(temp->content), i, env);
		}
		if (temp->token == PIPE)
		{
			i++;
		}
		temp = temp->next;
	}
}

static void	set_outfile(t_data *data, char **file, int block_id, char **env)
{
	char **arr;

	check_opened_outfiles(data, block_id);
	if (data->cmds_block[block_id].infile < 0 || data->cmds_block[block_id].fd_hd[0] < 0
		|| data->cmds_block[block_id].is_ambiguous == true)
		return ;
	cut_line_on(*file, &arr);
	join_arr_on(arr, file, env);
	// printf("le file c'est : ->%s<-\n", file);
	if (ft_strchr(*file, -32) != NULL)
	{
		data->cmds_block[block_id].outfile = -1;
		data->cmds_block[block_id].is_ambiguous = true;
		printf("je suis ambigue\n");
		return ;
	}
	data->cmds_block[block_id].outfile = open(*file, O_WRONLY | O_CREAT | \
	O_TRUNC, 0644);
	if (data->cmds_block[block_id].outfile == -1)
		perror("open outfile");
}

static void	set_appends(t_data *data, char **file, int block_id, char **env)
{	char **arr;

	check_opened_outfiles(data, block_id);
	if (data->cmds_block[block_id].infile < 0 || data->cmds_block[block_id].fd_hd[0] < 0
		|| data->cmds_block[block_id].is_ambiguous == true)
		return ;
	cut_line_on(*file, &arr);
	join_arr_on(arr, file, env);
	if (ft_strchr(*file, -32) != NULL)
	{
		data->cmds_block[block_id].outfile = -1;
		data->cmds_block[block_id].is_ambiguous = true;
		return ;
	}
	data->cmds_block[block_id].outfile = open(*file, O_WRONLY | O_CREAT | \
	O_APPEND, 0644);
	if (data->cmds_block[block_id].outfile == -1)
		perror("open outfile");
}
