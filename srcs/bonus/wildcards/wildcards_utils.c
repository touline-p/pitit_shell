/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:09:46 by twang             #+#    #+#             */
/*   Updated: 2023/05/09 19:10:54 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"
#include "minishell_parsing.h"

t_return_status	check_line(t_w_data *w_data, char *line)
{
	w_data->first = line[0];
	while (*line)
	{
		if (*line == '*')
			w_data->nb_of_stars++;
		if (*line == '/')
		{
			ft_dprintf(2, RED"minishell: /: bonus wildcards can be used only \
			in the current directory\n"END);
			return (FAILURE);
		}
		if (*(line + 1) == '\0')
			w_data->last = *line;
		line++;
	}
	if (w_data->nb_of_stars <= 0)
		return (FAILURE);
	return (SUCCESS);
}
