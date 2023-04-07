/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfiles_manage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:01:03 by twang             #+#    #+#             */
/*   Updated: 2023/04/07 18:56:53 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

/*---- prototypes ------------------------------------------------------------*/

static void	set_outfile(t_data *data, char *file, int block_id);
static void	set_appends(t_data *data, char *file, int block_id);

/*----------------------------------------------------------------------------*/

void	outfiles_management(t_data *data, t_string_token *string_of_tokens)
{
	int					i;
	t_string_token		*temp;

	i = 0;
	temp = string_of_tokens;
	display_str_token(string_of_tokens);
	while (temp != NULL)
	{
		if (temp->token == CHEVRON_OT)
		{
			temp = temp->next;
			set_outfile(data, temp->content, i);
		}
		if (temp->token == APPENDS)
		{
			temp = temp->next;
			set_appends(data, temp->content, i);
		}
		if (temp->token == PIPE)
		{
			i++;
		}
		temp = temp->next;
	}
}

static void	set_outfile(t_data *data, char *file, int block_id)
{
	if (data->cmds_block[block_id].outfile != 0)
		close(data->cmds_block[block_id].outfile);
	data->cmds_block[block_id].outfile = open(file, O_WRONLY | O_CREAT | \
	O_TRUNC, 0644);
	if (data->cmds_block[block_id].outfile == -1)
		perror("open outfile");
}

static void	set_appends(t_data *data, char *file, int block_id)
{
	if (data->cmds_block[block_id].outfile != 0)
		close(data->cmds_block[block_id].outfile);
	data->cmds_block[block_id].outfile = open(file, O_WRONLY | O_CREAT | \
	O_APPEND, 0644);
	if (data->cmds_block[block_id].outfile == -1)
		perror("open outfile");
}

/*
#define TEST_DEBUG
#ifdef TEST_DEBUG
#include "../srcs/debug_folder/debug.h"

int    main(void)
{
    debug;
    idebug(12);
    sdebug("Bonjour Thea");
    return (0);
}
#endif
*/