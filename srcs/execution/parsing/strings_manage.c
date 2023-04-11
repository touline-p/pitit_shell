/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_manage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:41:57 by twang             #+#    #+#             */
/*   Updated: 2023/04/11 18:44:11 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

/*---- prototypes ------------------------------------------------------------*/

// static bool	is_builtin(char *string);
static void	alloc_command(t_data *data, t_string_token *string_of_tokens);

/*----------------------------------------------------------------------------*/

void	strings_management(t_data *data, t_string_token *string_of_tokens)
{
	int				index;
	int				block_id;
	t_string_token	*temp;

	index = 0;
	block_id = 0;
	temp = string_of_tokens;
	alloc_command(data, string_of_tokens);
	while (temp != NULL)
	{
		if (temp->token == STRING)
		{
			data->cmds_block[block_id].commands[index] = \
			ft_strdup(temp->content);
			index++;
		}
		if (temp->token == PIPE)
		{
			block_id++;
			index = 0;
		}
		temp = temp->next;
	}
}

static void	alloc_command(t_data *data, t_string_token *string_of_tokens)
{
	t_string_token	*temp;
	int				size;
	int				block_id;

	size = 0;
	block_id = 0;
	temp = string_of_tokens;
	while (temp != NULL)
	{
		if (temp->token == STRING)
			size++;
		if (temp->token == PIPE)
		{
			data->cmds_block[block_id].commands = \
			malloc(sizeof(char *) * (size + 1));
			block_id++;
			size = 0;
		}
		temp = temp->next;
	}
	data->cmds_block[block_id].commands = malloc(sizeof(char *) * (size + 1));
}

/*
static bool	is_builtin(char *string)
{
	if (ft_strcmp(string, "echo") == 0 || ft_strcmp(string, "cd") == 0 || 
	ft_strcmp(string, "pwd") == 0 || ft_strcmp(string, "export") == 0 || 
	ft_strcmp(string, "unset") == 0 || ft_strcmp(string, "env") == 0 || 
	ft_strcmp(string, "exit") == 0)
		return (true);
	else
		return (false);
}
*/