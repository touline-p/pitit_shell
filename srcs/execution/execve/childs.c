/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:17:52 by twang             #+#    #+#             */
/*   Updated: 2023/04/17 19:38:41 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

/*---- prototypes ------------------------------------------------------------*/

static void	wait_for_process_ids(t_data *data);

/*----------------------------------------------------------------------------*/

t_return_status	childs_execve(t_data *data, char **env)
{
	int		block_id;
	char	*command;

	block_id = 0;
	while (block_id < data->nb_of_pipe + 1)
	{
		if (pipe(data->cmds_block[block_id].fd) == -1)
			return (FAILED_PIPE);
		data->cmds_block[block_id].process_id = fork();
		if (data->cmds_block[block_id].process_id == 0)
		{
			close_fds(data, block_id);
			duplicate_fds(data, block_id);
			command = add_path_cmd(block_id, data, env);
			execve(command, data->cmds_block[block_id].commands[block_id], env);
			exit(FAILURE);
		}
		else if (data->cmds_block[block_id].process_id < 0)
		{
			ft_dprintf(2, RED"Fork Issue: Resource temporarily unavailable\n"END);
			break ;
		}
		block_id++;
	}
	close_all_fds(data, block_id);
}

static void	wait_for_process_ids(t_data *data)
{
	int	block_id;
	int	status;

	block_id = 0;
	status = 0;
	while (block_id < data->nb_of_pipe + 1)
	{
		waitpid(data->cmds_block[block_id].process_id, &status, 0);
		if (WEXITSTATUS(status) && block_id == data->nb_of_pipe)
			exit(127);
		block_id++;
	}
}
