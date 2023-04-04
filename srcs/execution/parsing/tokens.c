/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:41:03 by twang             #+#    #+#             */
/*   Updated: 2023/04/04 19:58:53 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"


/*---- prototypes ------------------------------------------------------------*/

static void	heredoc_recognition(t_data *data, t_string_token *string_of_tokens);
static void	files_recognition(t_data *data, t_string_token *string_of_tokens);
static void	strings_recognition(t_data *data, t_string_token *string_of_tokens);

/*----------------------------------------------------------------------------*/

void	token_recognition(t_data *data, t_string_token *string_of_tokens)
{
	heredoc_recognition(data, string_of_tokens);
	//wait for end of heredoc.
	files_recognition(data, string_of_tokens);
	display_str_token(string_of_tokens);
	clean_files_token(string_of_tokens);
	clean_token(string_of_tokens);
	strings_recognition(data, string_of_tokens);
}

static void	heredoc_recognition(t_data *data, t_string_token *string_of_tokens)
{
	t_string_token	*temp;

	temp = string_of_tokens;
	while (temp != NULL)
	{
		if (temp->token == PIPE)
			data->nb_of_pipes++;
		if (temp->token == HERE_DOC)
		{
			temp = temp->next;
			heredoc_management(data, temp->content);
		}
		temp = temp->next;
	}
}

static void	files_recognition(t_data *data, t_string_token *string_of_tokens)
{
	t_string_token	*temp;
	t_token_minishell token;

	temp = string_of_tokens;
	while (temp != NULL)
	{
		if (temp->token == CHEVRON_IN || temp->token == CHEVRON_OT || \
			temp->token == APPENDS)
		{
			token = temp->token;
			temp = temp->next;
			files_management(data, temp->content, token);
		}
		temp = temp->next;
	}
}

static void	strings_recognition(t_data *data, t_string_token *string_of_tokens)
{
	t_string_token	*temp;

	(void)data;
	temp = string_of_tokens;
	while (temp != NULL)
	{
		if (temp->token == STRING)
			strings_management(data, string_of_tokens, temp->content);
		temp = temp->next;
	}
}
