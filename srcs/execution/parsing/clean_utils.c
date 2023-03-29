/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 20:00:13 by twang             #+#    #+#             */
/*   Updated: 2023/03/29 20:00:31 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

void	clean_files_token(t_string_token *string_of_tokens)
{
	t_string_token	*temp;

	temp = string_of_tokens;
	while (temp != NULL)
	{
		if (temp->next->token == CHEVRON_IN || temp->next->token == CHEVRON_OT || \
			temp->next->token == APPENDS)
			del_next_string_token(temp);
		else
			temp = temp->next;
	}
}
