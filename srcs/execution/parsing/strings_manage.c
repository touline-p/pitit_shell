/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_manage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangthea <wangthea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:41:57 by twang             #+#    #+#             */
/*   Updated: 2023/04/06 23:42:23 by wangthea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

/*---- prototypes ------------------------------------------------------------*/

static bool	is_builtin(char *string);
static void	get_command(t_data *data, t_string_token *str_of_tok, char *string);

/*----------------------------------------------------------------------------*/

void	strings_management(t_data *data, t_string_token *str_of_tok, char *str)
{
	(void)data;
	(void)str_of_tok;
	if (is_builtin(str) == true)
		puts(RED"c'est un builtin"END);
	else
	{
		puts(GREEN"c'est une commande"END);
		get_command(data, str_of_tok, str);
	}
}

static bool	is_builtin(char *string)
{
	if (ft_strcmp(string, "echo") == 0 || ft_strcmp(string, "cd") == 0 || \
	ft_strcmp(string, "pwd") == 0 || ft_strcmp(string, "export") == 0 || \
	ft_strcmp(string, "unset") == 0 || ft_strcmp(string, "env") == 0 || \
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
