/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 10:03:57 by twang             #+#    #+#             */
/*   Updated: 2023/05/16 17:37:09 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"
#include "minishell_parsing.h"

t_return_status	check_arguments(char **av)
{
	if (av[1] != NULL)
	{
		ft_dprintf(2, "minishell: %s: ", av[1]);
		ft_dprintf(2, "the arguments are not processed.\n");
		ft_dprintf(2, YELLOW"usage: ");
		ft_dprintf(2, "please run the program without any arguments.\n"END);
		return (FAILURE);
	}
	else
		return (SUCCESS);
}

void	clean_the_prompt(char *prompt, char *line, char **env)
{
	free(line);
	if (line == NULL)
	{
		free(prompt);
		ft_free_split(env);
		clear_history();
		ft_dprintf(1, RED"exit\n"END);
		exit(0);
	}
}
