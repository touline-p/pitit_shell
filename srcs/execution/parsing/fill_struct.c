/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 20:14:11 by twang             #+#    #+#             */
/*   Updated: 2023/04/05 20:22:42 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

/*---- prototypes ------------------------------------------------------------*/

static void	cmds_block_alloc(t_data *data, t_string_token *string_of_tokens);

/*----------------------------------------------------------------------------*/

static void	cmds_block_alloc(t_data *data, t_string_token *string_of_tokens)
{
	int					pipes;
	t_string_of_token	*temp;

	pipes = 0;
	temp = string_of_tokens;
	while (temp != NULL)
	{
		if (temp->token == PIPE)
		{
			pipes++;
			data->nb_of_cmd = pipes + 1;
		}
		temp = temp->next;
	}
	data->cmds_block = (t_cmd *)malloc((data->nb_of_cmds + 1) * sizeof(t_cmd));
}

void	fill_struct(t_data *data, t_string_token *string_of_tokens)
{
	cmds_block_alloc(data, string_of_tokens);
}
