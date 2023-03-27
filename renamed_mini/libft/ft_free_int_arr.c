/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_int_arr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <bpoumeau@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 22:03:33 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/03/10 22:04:38 by bpoumeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_int_arr(int **int_arr)
{
	int **tmp;

	tmp = int_arr;
	while (*int_arr)
	{
		free(*int_arr);
		int_arr++;
	}
	free(tmp);
}