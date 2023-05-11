/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:27:19 by twang             #+#    #+#             */
/*   Updated: 2023/05/11 17:09:27 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"
#include "minishell_parsing.h"

/*---- prototypes ------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/

static char	**fetch_wildcards_args(char *line)
{	
	if (parse_args(line) != SUCCESS)
	{
		ft_dprintf(2, RED"%s\n"END, line);
		return (NULL);
	}
	/*if (fetch_args(line) != SUCCESS)
	{
		return (FAILURE);
	}*/
	return (NULL);
}
/*
t_return_status	wildcards(t_data *data)
{
	int i;

	i = 0;
	while(data->cmds_block->commands[i])
	{
		printf(data->cmds_block->commands[i]);
		printf(data->cmds_block->commands[i][0]);
		fetch_wildcards_args(data->cmds_block[i].commands[i]);
		i++;
	}
}
*/
// #define TST_WILD
#ifdef TST_WILD

int	main(int ac, char **av)
{
	(void)ac; (void)av;
	char *line = "i*c*s";
	char **wildcards;

	wildcards = fetch_wildcards_args(line);
	// puts("result : ");
	ft_print_split(wildcards);
	return (0);
}

#endif
