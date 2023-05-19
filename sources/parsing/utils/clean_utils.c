/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 20:00:13 by twang             #+#    #+#             */
/*   Updated: 2023/05/17 17:59:31 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_files_token(t_string_token *lst_of_tok)
{
	t_string_token	*temp;

	temp = lst_of_tok;
	while (temp != NULL)
	{
		if (temp->token == O_PRTSS)
			go_to_next_(C_PRTSS, temp->next, &temp);
		if (temp->token == CHEVRON_IN || temp->token == CHEVRON_OT || \
			temp->token == APPENDS || temp->token == HERE_DOC)
		{
			del_next_string_token(temp);
		}
		temp = temp->next;
	}
}

void	clean_token(t_string_token *lst_of_tok)
{
	t_string_token	*temp;

	temp = lst_of_tok;
	while (temp->next != NULL)
	{
		if (temp->token == O_PRTSS)
			go_to_next_(C_PRTSS, temp->next, &temp);
		if (temp->next->token == CHEVRON_IN || temp->next->token == CHEVRON_OT \
		|| temp->next->token == APPENDS || temp->next->token == HERE_DOC)
			del_next_string_token(temp);
		else
			temp = temp->next;
	}
}
