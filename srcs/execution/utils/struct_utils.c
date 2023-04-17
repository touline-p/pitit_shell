/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:10:03 by twang             #+#    #+#             */
/*   Updated: 2023/04/17 14:39:14 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

void	free_commands(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_pipe + 2)
	{
		ft_free((void **)data->cmds_block[i].commands, data->nb_of_pipe + 1);
		i++;
	}
}
