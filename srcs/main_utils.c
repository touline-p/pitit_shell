/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 10:03:57 by twang             #+#    #+#             */
/*   Updated: 2023/05/08 14:58:30 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"
#include "minishell_parsing.h"


t_return_status	check_arguments(int ac, char **av)
{
	if (ac != 1)
	{
		ft_dprintf(2, "minishell: %s: the arguments are not processed.\n", av[1]);
		ft_dprintf(2, YELLOW"usage: please run the program without any arguments.\n"END);
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
		//ft_dprintf(1, "exit");
		exit(0);
	}
}