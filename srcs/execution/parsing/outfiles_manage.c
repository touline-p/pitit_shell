/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfiles_manage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:01:03 by twang             #+#    #+#             */
/*   Updated: 2023/05/05 15:13:39 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"
#include "../../incs/parsing_incs/minishell_parsing.h"

/*---- prototypes ------------------------------------------------------------*/

//static t_return_status	_set_outfile(t_data *data, char **file, \
//									int block_id, char **env);
//static t_return_status	_set_appends(t_data *data, char **file, \
//									int block_id, char **env);

/*----------------------------------------------------------------------------*/

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
	cmd->outfile = -1;
	cmd->is_ambiguous = true;
	false_space_to_space(file);
	ft_dprintf(2, "minishell: %s: ambiguous redirect\n", file);
}

t_return_status	outfiles_management(t_data *data, \
									t_string_token *lst_of_tok, char **env)
{
	(void)data, (void)lst_of_tok, (void)env;
	return (SUCCESS);
	int					i;
	t_string_token		*temp;

	i = 0;
	temp = lst_of_tok;
	while (temp != NULL)
	{

		if (temp->token == PIPE)
			i++;
		temp = temp->next;
	}
	return (SUCCESS);
}

