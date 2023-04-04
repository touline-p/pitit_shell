/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_manage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:41:57 by twang             #+#    #+#             */
/*   Updated: 2023/04/04 19:17:37 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

/*---- prototypes ------------------------------------------------------------*/

static bool	is_builtin(char *string);

/*----------------------------------------------------------------------------*/

void	strings_management(t_data *data, char *string)
{
	(void)data;
	if (is_builtin(string) == true)
		puts(RED"c'est un builtin"END);
	else
		puts(GREEN"c'est une commande"END);
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