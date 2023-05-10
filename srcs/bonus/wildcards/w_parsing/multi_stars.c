/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_stars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:41:16 by twang             #+#    #+#             */
/*   Updated: 2023/05/10 11:47:35 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"
#include "minishell_parsing.h"

/*---- prototypes ------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/

t_return_status	multi_stars_case(t_w_data *w_data, char *line, char *name)
{
	(void)w_data;
	(void)line;
	(void)name;
	puts("Voila c'est pas fait !");
	return (FAILURE);
}