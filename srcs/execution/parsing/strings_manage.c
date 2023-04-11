/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_manage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:41:57 by twang             #+#    #+#             */
/*   Updated: 2023/04/11 15:22:17 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

/*---- prototypes ------------------------------------------------------------*/

// static void	set_commands(t_data *data, char *string, int block_id);
// static bool	is_builtin(char *string);
// static void	get_command(t_data *data, t_string_token *str_of_tok, char *string);

/*----------------------------------------------------------------------------*/

void	strings_management(t_data *data, t_string_token *string_of_tokens)
{
	(void)data;
	
	int				i;
	t_string_token	*temp;

	i = 0;
	temp = string_of_tokens;
	/*alloue pour *command -une fois commande rempli -join de reste et puis split pour **args */
	while (temp != NULL)
	{
		if (temp->token == STRING)
		{
			puts("je n'ai pas encore gerer les string!");
			// set_commands(data, temp->content, i);
		}
		if (temp->token == PIPE)
		{
			i++;
		}
		temp = temp->next;
	}
}
/*
static void	set_commands(t_data *data, char *string, int block_id)
{
	(void)data;
	printf(BLUE"%s\n"END, string);
	printf(BLUE"%d\n"END, block_id);
	if (data->cmds_block[block_id].commands[0] == NULL)
	{
		data->cmds_block[block_id].commands[0][0] = ft_strdup(string);
		printf("commands : %c\n", data->cmds_block[block_id].commands[0]);
	}
	// else
	// {
		// data->cmds_block[block_id].commands[0][0] = ft_strdup(string);
		// printf("commands : %s\n", data->cmds_block[block_id].commands[0]);
		// printf("argument : %s\n", data->cmds_block[block_id].commands[0][0]);
	// }
	
	premier appel = command[0];
	second appel = command[0][0];
	
}*/
/*
	(void)data;
	(void)str_of_tok;
	if (is_builtin(str) == true)
		puts(RED"c'est un builtin"END);
	else
	{
		puts(GREEN"c'est une commande"END);
		get_command(data, str_of_tok, str);
	}
	
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

static void	get_command(t_data *data, t_string_token *str_of_tok, char *string)
{
	(void)data;
	(void)str_of_tok;
	printf(PURPLE"%s\n"END, string);
	display_str_token(str_of_tok);
}
*/