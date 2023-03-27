/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_ert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 19:11:04 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/02/13 19:11:11 by bpoumeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	put_ert(t_ert code)
{
	if (code == SUCCESS)
		write(1, "SUCCESS\n", 8);
	if (code == FAILURE)
		write(1, "FAILURE\n", 8);
	if (code == MLC_ERR)
		write(1, "MLC_ERR\n", 8);
}
