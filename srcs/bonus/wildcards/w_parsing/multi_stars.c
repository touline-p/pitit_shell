/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_stars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:41:16 by twang             #+#    #+#             */
/*   Updated: 2023/05/11 15:16:41 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"
#include "minishell_parsing.h"
#include <string.h>

/*---- prototypes ------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/

t_return_status	multi_stars_case(t_w_data *w_data, char *line, char *name)
{
	while (*line)
	{
		while (*line == '*' && *(line + 1) == '*')
			line++;
		if (*line == '*')
		{
			line++;
 			name = ft_strstr_w(name, line);
		}
		if (!name || (*line && *line != '*' && *name != *line))
		{
			return (FAILURE);
		}
		line++;
		name++;
	}
	return (SUCCESS);
}