/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangthea <wangthea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:10:03 by twang             #+#    #+#             */
/*   Updated: 2023/04/24 20:56:11 by wangthea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

void	free_commands(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_pipe + 1)
	{
		if (data->cmds_block[i].id_command == CMD)
			ft_free((void **)data->cmds_block[i].commands, data->nb_of_pipe + 1);
		i++;
	}
}

t_return_status free_data(t_data *data)
{
	int	i;
	int	j;
	
    if (!data || !data->cmds_block)
		return (FAILURE);
	i = 0;
	while (i < data->nb_of_pipe + 2)
	{
		if (data->cmds_block[i].commands != NULL)
		{
			ft_free((void **)data->cmds_block[i].commands, data->nb_of_pipe + 1);
		}
		i++;
	}
    free(data->cmds_block);
	free(data);
	return (SUCCESS);
}
