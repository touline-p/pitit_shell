/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:10:03 by twang             #+#    #+#             */
/*   Updated: 2023/04/28 16:07:37 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

t_return_status	free_commands(t_data *data)
{
	int	i;

 	if (!data->cmds_block)
		return (FAILURE);
	i = 0;
	while (i < data->nb_of_pipe + 1)
	{
		if (data->cmds_block[i].id_command == CMD)
			ft_free((void **)data->cmds_block[i].commands, data->nb_of_pipe + 1);
		i++;
	}
	return (SUCCESS);
}
