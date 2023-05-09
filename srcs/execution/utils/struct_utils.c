/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:10:03 by twang             #+#    #+#             */
/*   Updated: 2023/05/03 10:57:04 by twang            ###   ########.fr       */
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
void	ft_free_all_str_lst(t_data *data, int index)
{
	index++;
	while (data->instructions_arr[index])
		string_token_destructor(data->instructions_arr[index++]);
	free(data->instructions_arr);
	return ;
}
