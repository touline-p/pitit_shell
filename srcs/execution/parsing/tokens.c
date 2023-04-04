/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:41:03 by twang             #+#    #+#             */
/*   Updated: 2023/04/04 16:17:43 by twang            ###   ########.fr       */
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
			puts(BLUE"before"END);
			display_str_token(string_of_tokens);
		}
		temp = temp->next;
	}
	puts(PURPLE"youpiyayayoupiyoupiya"END);
	clean_files_token(string_of_tokens);
	clean_token(string_of_tokens);
	display_str_token(string_of_tokens);
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
//#define TST_TOKENS
#ifdef TST_TOKENS
#include "minishell_parsing.h"
t_return_status get_lexed_str_token_lst_from_line(char *line, t_string_token **str_tok_pt, char **env);

int main(int ac, char **av, char **env)
{
	(void)ac; (void)av;
	t_string_token	*tst;
	printf("we are herre\n");
	get_lexed_str_token_lst_from_line(av[1], &tst, env);
	display_str_token(tst);

	clean_files_token(tst);
	display_str_token(tst);
	clean_token(tst);
	display_str_token(tst);
	string_token_destructor(tst);
	return (0);
}

#endif