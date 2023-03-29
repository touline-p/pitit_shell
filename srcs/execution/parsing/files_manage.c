/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_manage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:01:03 by twang             #+#    #+#             */
/*   Updated: 2023/03/29 20:01:05 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

/*---- prototypes ------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/

void	files_management(t_data *data, char *file, t_token_minishell token)
{
	if (token == CHEVRON_IN)
	{
		if (data->infile != 0)
			close(data->infile);
		data->infile = open(file, O_RDONLY, 0644);
		if (data->infile == -1)
			perror("open infile");
	}
	else 
	{
		if (data->outfile != 0)
			close(data->outfile);
		if (token == CHEVRON_OT)
			data->outfile = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			data->outfile = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (data->outfile == -1)
			perror("open outfile");
	}
}
