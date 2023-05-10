/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:27:19 by twang             #+#    #+#             */
/*   Updated: 2023/05/10 15:47:42 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"
#include "minishell_parsing.h"

/*---- prototypes ------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/

t_return_status	fetch_wildcards_args(char *line)
{
	t_w_data	w_data;
	
	ft_bzero((void *)&w_data, sizeof(t_w_data));
	if (parse_args(&w_data, line) != SUCCESS)
	{
		ft_dprintf(2, RED"%s\n"END, line);
		return (FAILURE);
	}
	return (SUCCESS);
}

// #define TST_WILD
#ifdef TST_WILD

int	main(int ac, char **av)
{
	(void)ac; (void)av;
	char *line = "*";

	fetch_wildcards_args(line);
	return (0);
}

#endif
