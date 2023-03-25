/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_tokens_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <bpoumeau@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:03:28 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/03/11 17:26:28 by bpoumeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by bpoumeau on 3/11/23.
//

#include "mini_parsing.h"

t_ert	is_control_operator(t_emt token)
{
	if (token == PIPE || token == OR || token == AMPERSAND || token == AND)
		return (SUCCESS);
	return (FAILURE);
}
