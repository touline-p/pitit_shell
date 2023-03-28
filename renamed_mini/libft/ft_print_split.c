/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <bpoumeau@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 23:45:17 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/03/10 19:13:11 by bpoumeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_split(char **split)
{
	if (split == NULL)
	{
		printf("Null\n");
		return ;
	}
	while (*split)
	{
		if (write(1, *split, ft_strlen(*split)) == -1
			|| write(1, "\n", 1) == -1)
			write(2, "Error write ft_print_split", 26);
		split++;
	}
}
