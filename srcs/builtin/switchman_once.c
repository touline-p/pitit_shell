//
// Created by bpoumeau on 4/22/23.
//

#include "../../incs/execution_incs/minishell_execution.h"
#include "../../incs/parsing_incs/minishell_parsing.h"

t_return_status	switchman_once(t_data *data, char ***env_pt)
{
	int pid;
	if (data->cmds_block->id_command > PWD
		|| (data->cmds_block->id_command == EXPORT && data->cmds_block->commands[1] != NULL))
		return (builtin_switch(data->cmds_block->id_command, data->cmds_block->commands, env_pt));
	pid = fork();
	if (pid == 0)
	{
		duplicate_fds(data, 0);
		builtin_switch(data->cmds_block->id_command, data->cmds_block->commands, env_pt);
		exit(g_ret_val);
	}
	return (SUCCESS);
}