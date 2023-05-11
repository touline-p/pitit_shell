/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:27:19 by twang             #+#    #+#             */
/*   Updated: 2023/05/11 19:27:48 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"
#include "minishell_parsing.h"

/*---- prototypes ------------------------------------------------------------*/

static t_return_status	fetch_wildcards_args(char *line);

/*----------------------------------------------------------------------------*/

t_return_status	wildcards(t_data *data)
{
	(void)data;
	puts("voila");
	// int i;

	// i = 0;
	// while(data->cmds_block->commands[i])
	// {
	// 	printf("%s\n", data->cmds_block->commands[i]);
	// 	fetch_wildcards_args("l*");
	// 	i++;
	// }
	return (FAILURE);
}

static t_return_status	fetch_wildcards_args(char *line)
{	
	if (parse_args(line) != SUCCESS)
	{
		ft_dprintf(2, RED"%s\n"END, line);
		return (FAILURE);
	}
	/*if (fetch_files(line) != SUCCESS)
	{
		return (FAILURE);
	}*/
	return (SUCCESS);
}
