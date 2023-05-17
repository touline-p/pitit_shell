/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfiles_manage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:01:03 by twang             #+#    #+#             */
/*   Updated: 2023/05/17 18:14:20 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	false_space_to_space(char *str)
{
	while (*str)
	{
		if (*str == -32)
			*str = 32;
		str++;
	}
}

void	manage_ambiguous(t_cmd *cmd, char *file)
{
	cmd->is_ambiguous = true;
	false_space_to_space(file);
	ft_dprintf(2, "minishell: %s: ambiguous redirect\n", file);
}
