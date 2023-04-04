/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 20:00:13 by twang             #+#    #+#             */
/*   Updated: 2023/04/04 17:53:46 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

void	clean_files_token(t_string_token *string_of_tokens)
{
	t_string_token	*temp;

	temp = string_of_tokens;
	while (temp != NULL)
	{
		if (temp->token == CHEVRON_IN || temp->token == CHEVRON_OT || \
			temp->token == APPENDS || temp->token == HERE_DOC)
		{
			del_next_string_token(temp);
		}

		temp = temp->next;
	}
}

void	clean_token(t_string_token *string_of_tokens)
{
	t_string_token	*temp;

	temp = string_of_tokens;
	while (temp->next != NULL)
	{
		if (temp->next->token == CHEVRON_IN || temp->next->token == CHEVRON_OT || \
			temp->next->token == APPENDS || temp->next->token == HERE_DOC)
			del_next_string_token(temp);
		else
			temp = temp->next;
	}
}
