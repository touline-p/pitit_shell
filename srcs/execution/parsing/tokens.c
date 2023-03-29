/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:41:03 by twang             #+#    #+#             */
/*   Updated: 2023/03/29 20:24:28 by twang            ###   ########.fr       */
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
	files_recognition(data, string_of_tokens);
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
		else if (temp->token == HERE_DOC)
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
			display_str_token(string_of_tokens);
			clean_files_token(string_of_tokens);
			display_str_token(string_of_tokens);
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
		{
			puts("string");
		}
		temp = temp->next;
	}
}
